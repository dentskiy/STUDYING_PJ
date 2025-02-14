#include "smodel.h"

#include <cstdlib>
#include <ctime>

#define EMPTY_CELL s21::kEmptyCell
#define SNAKE_CELL s21::kMoveCell
#define APPLE_CELL s21::kStaticCell
#define HIGH_POSIBLE_SCORE (s21::kCellCount - 4)

namespace {
constexpr const int level[] = {30, 28, 26, 22, 20, 18, 17, 16, 15, 12};
}

using std::srand;

namespace s21 {
SnakeModel::SnakeModel(const char* filename) : snake_{}, sFace_{} {
  this->fManager_.SetFilename(filename);
  SnakeModel::ClearModel();
  SnakeModel::InitModel();
  this->modelData_.pause = ModelPause;
  this->level_ = ::level;
}

SnakeModel::~SnakeModel() {
  SnakeModel::ClearModel();
  this->level_ = nullptr;
}

// privat:

// override ==============================================================

void SnakeModel::InitModel() {
  this->modelData_.high_score = this->fManager_.GetSave();
  srand(time(0));
  for (int i{}; i < 4; i++) {
    this->modelData_.field[0][i] = SNAKE_CELL;
    snake_.push(pos(i, 0));
  }
  this->count_ = 0;
  this->modelData_.level = 1;
  this->modelData_.score = 0;
  sFace_(1, 0);
  SpawnApple();
}

void SnakeModel::ClearModel() {
  if (this->modelData_.score > this->modelData_.high_score)
    this->fManager_.SetSave(this->modelData_.score);

  while (!snake_.empty()) snake_.pop();
  for (int i{}; i < kHeight; i++) {
    for (int j{}; j < kWidth; j++) {
      this->modelData_.field[i][j] = EMPTY_CELL;
    }
  }
}

bool SnakeModel::Move() {
  int head_X(snake_.back().x + sFace_.x);
  int head_Y(snake_.back().y + sFace_.y);
  bool res = CheckCell(head_X, head_Y);
  if (res) {
    if (this->modelData_.field[head_Y][head_X] == APPLE_CELL) {
      EatApple();
      if (this->modelData_.score < HIGH_POSIBLE_SCORE)
        SpawnApple();
      else
        res = false;
    } else {
      SnakeMove();
    }
  }
  return res;
}

void SnakeModel::PlayMenu(UserAction_t signal) {
  switch (signal) {
    case Pause:
      this->modelData_.pause = ModelPause;
      break;
    case Terminate:
      Clash();
      break;
    case Left:
      if (sFace_.x != 1) {
        sFace_(-1, 0);
        this->count_ = ::level[0];
      }
      break;
    case Right:
      if (sFace_.x != -1) {
        sFace_(1, 0);
        this->count_ = ::level[0];
      }
      break;
    case Up:
      if (sFace_.y != 1) {
        sFace_(0, -1);
        this->count_ = ::level[0];
      }
      break;
    case Down:
      if (sFace_.y != -1) {
        sFace_(0, 1);
        this->count_ = ::level[0];
      }
      break;
    case Action:
      this->count_ = ::level[0];
      break;
    default:;
  }
  FSMachine({}, false);
}

void SnakeModel::Clash() { this->modelData_.pause = GameOver; }

// =======================================================================

void SnakeModel::EatApple() {
  snake_.push(pos(snake_.back().x + sFace_.x, snake_.back().y + sFace_.y));
  this->modelData_.field[snake_.back().y][snake_.back().x] = SNAKE_CELL;
  this->modelData_.score += 1;
  if (this->modelData_.level != 10 && !(this->modelData_.score % 5))
    this->modelData_.level += 1;
}

void SnakeModel::SnakeMove() {
  snake_.push(pos(snake_.back().x + sFace_.x, snake_.back().y + sFace_.y));
  this->modelData_.field[snake_.front().y][snake_.front().x] = EMPTY_CELL;
  this->modelData_.field[snake_.back().y][snake_.back().x] = SNAKE_CELL;
  snake_.pop();
}

void SnakeModel::SpawnApple() {
  int num = rand() % kCellCount;
  int i{num / 10}, j{num % 10};
  for (; this->modelData_.field[i][j]; i == (kHeight - 1) ? i = 0 : i++) {
    for (; j < kWidth && this->modelData_.field[i][j]; j++);
    if (j == kWidth)
      j = 0;
    else
      i == 0 ? i = s21::kHeight - 1 : i--;
  }
  this->modelData_.field[i][j] = APPLE_CELL;
}

bool SnakeModel::CheckCell(int x, int y) {
  bool res = x >= 0 && x < kWidth;
  res = res && y >= 0 && y < kHeight;
  res = res && this->modelData_.field[y][x] != SNAKE_CELL;
  res = res || (x == snake_.front().x && y == snake_.front().y);
  return res;
}
}  // namespace s21
