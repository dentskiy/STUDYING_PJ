#include "tmodel.h"

#include <cstdlib>
#include <ctime>

namespace {
constexpr const int level[] = {30, 28, 26, 22, 20, 18, 17, 16, 15, 12};
constexpr const int score[] = {100, 300, 700, 1500};

bool CheckW(int n) { return n >= 0 && n < s21::kWidth; }
bool CheckH(int n) { return n >= 0 && n < s21::kHeight; }
bool CheckRow(int* row) {
  int res = true;
  for (int i{}; res && i < s21::kWidth; i++) {
    res = row[i] == s21::kStaticCell;
  }
  return res;
}
bool CheckNEmptyRow(int* row) {
  int res = false;
  for (int i{}; !res && i < s21::kWidth; i++) {
    res = row[i] == s21::kStaticCell;
  }
  return res;
}
}  // namespace

using std::srand;

namespace s21 {

TetrisModel::TetrisModel(const char* filename) {
  this->fManager_.SetFilename(filename);
  this->modelData_.next = new int*[4]{};
  for (int i{}; i < 4; i++) {
    this->modelData_.next[i] = new int[4]{};
  }
  TetrisModel::ClearModel();
  TetrisModel::InitModel();
  this->modelData_.pause = ModelPause;
  this->level_ = ::level;
}

TetrisModel::~TetrisModel() {
  TetrisModel::ClearModel();
  this->level_ = nullptr;
  for (int i{}; i < 4; i++) {
    delete[] this->modelData_.next[i];
  }
  delete[] this->modelData_.next;
  this->modelData_.next = nullptr;
}

// privat:

// override ==============================================================

void TetrisModel::InitModel() {
  this->modelData_.high_score = this->fManager_.GetSave();
  srand(time(0));
  nFrameNext_ = rand() % 7;
  tBag_[nFrameNext_] = true;
  SpawnObject();
  this->count_ = 0;
  this->modelData_.level = 1;
  this->modelData_.score = 0;
}

void TetrisModel::ClearModel() {
  if (this->modelData_.score > this->modelData_.high_score)
    this->fManager_.SetSave(this->modelData_.score);

  for (int i{}; i < kHeight; i++) {
    for (int j{}; j < kWidth; j++) {
      this->modelData_.field[i][j] = kEmptyCell;
    }
  }
  ClearFrame(this->modelData_.next, {0, 0});
  for (int i{}; i < 7; i++) tBag_[i] = false;
}

bool TetrisModel::Move() {
  bool res;
  ClearFrame(this->modelData_.field, fPosition_);
  fPosition_.y += 1;
  if (!(res = CheckMove())) fPosition_.y -= 1;
  PrintFrame(this->modelData_.field, fPosition_, nFrame_, rFrame_);
  return res;
}

void TetrisModel::PlayMenu(UserAction_t signal) {
  ClearFrame(this->modelData_.field, fPosition_);
  switch (signal) {
    case Pause:
      this->modelData_.pause = ModelPause;
      break;
    case Terminate:
      this->modelData_.pause = GameOver;
      break;
    case Left:
      fPosition_.x -= 1;
      if (!CheckMove()) fPosition_.x += 1;
      break;
    case Right:
      fPosition_.x += 1;
      if (!CheckMove()) fPosition_.x -= 1;
      break;
    case Up:
      RotateUp();
      if (!CheckMove()) RotateDown();
      break;
    case Down:
      this->count_ = ::level[0];
      break;
    case Action:
      while (Move());
      this->count_ = ::level[0];
      break;
    default:;
  }
  PrintFrame(this->modelData_.field, fPosition_, nFrame_, rFrame_);
  this->FSMachine({}, false);
}

void TetrisModel::Clash() {
  FixMovedCell();
  UpdateScore();
  CheckGameOver();
  SpawnObject();
}

// =======================================================================

void TetrisModel::PrintFrame(int** map, pos p, int num, int rot) {
  for (int i{}; i < 4; i++) {
    for (int j{}; CheckH(p.y + i) && j < 4; j++) {
      if (CheckW(p.x + j) && frames_[num][rot][i][j] == 1)
        map[p.y + i][p.x + j] = kMoveCell;
    }
  }
}
void TetrisModel::ClearFrame(int** map, pos p) {
  for (int i{}; i < 4; i++) {
    for (int j{}; j < 4 && CheckH(p.y + i); j++) {
      if (CheckW(p.x + j) && map[p.y + i][p.x + j] == kMoveCell)
        map[p.y + i][p.x + j] = kEmptyCell;
    }
  }
}

bool TetrisModel::CheckMove() {
  bool res = true;
  pos& p = fPosition_;
  for (int i{}; res && i < 4; i++) {
    for (int j{}; res && j < 4 && (i + p.y) >= 0; j++) {
      if (frames_[nFrame_][rFrame_][i][j]) {
        res = res && ::CheckW(j + p.x);
        res = res && ((i + p.y) < kHeight);
        res = res && (this->modelData_.field[i + p.y][j + p.x] == kEmptyCell);
      }
    }
  }
  return res;
}

void TetrisModel::FixMovedCell() {
  pos& p = fPosition_;
  for (int i{p.y}; i < (p.y + 4); i++) {
    for (int j{p.x}; j < (p.x + 4) && CheckH(i); j++) {
      if (CheckW(j) && this->modelData_.field[i][j] == kMoveCell) {
        this->modelData_.field[i][j] = kStaticCell;
      }
    }
  }
}

void TetrisModel::RotateUp() { rFrame_ == 3 ? rFrame_ = 0 : rFrame_++; }
void TetrisModel::RotateDown() { rFrame_ ? rFrame_-- : rFrame_ = 3; }

bool TetrisModel::CheckBag() {
  return tBag_[0] && tBag_[1] && tBag_[2] && tBag_[3] && tBag_[4] && tBag_[5] &&
         tBag_[6];
}

void TetrisModel::SpawnObject() {
  nFrame_ = nFrameNext_;
  fPosition_(3, -1);
  rFrame_ = 0;
  nFrameNext_ = rand() % 7;
  if (CheckBag()) {
    for (int i{}; i < 7; i++) tBag_[i] = false;
  }
  while (tBag_[nFrameNext_]) nFrameNext_ == 6 ? nFrameNext_ = 0 : nFrameNext_++;
  tBag_[nFrameNext_] = true;
  ClearFrame(this->modelData_.next, {0, 0});
  PrintFrame(this->modelData_.next, {0, 0}, nFrameNext_, {});
  if (!CheckMove()) this->modelData_.pause = GameOver;
  PrintFrame(this->modelData_.field, fPosition_, nFrame_, rFrame_);
}

void TetrisModel::UpdateScore() {
  int rowCount = 0;
  for (int i{fPosition_.y}; i < fPosition_.y + 4; i++) {
    if (CheckH(i) && CheckRow(this->modelData_.field[i])) {
      rowCount++;
      delete[] this->modelData_.field[i];
      this->modelData_.field[i] = nullptr;
    }
  }
  for (int i{fPosition_.y + 3}, j{i}; j >= 0; i--) {
    while (!CheckH(i)) {
      i--;
    }

    while (i >= 0 && this->modelData_.field[i]) i--;
    j = i;
    while (j >= 0 && !this->modelData_.field[j]) j--;
    if (j >= 0) {
      this->modelData_.field[i] = this->modelData_.field[j];
      this->modelData_.field[j] = nullptr;
    }
  }
  for (int i{}; i < 4; i++) {
    if (!this->modelData_.field[i]) {
      this->modelData_.field[i] = new int[kWidth]{};
    }
  }
  this->modelData_.score += ::score[rowCount - 1];
  if (this->modelData_.level != 10)
    this->modelData_.level = (this->modelData_.score / 1000) + 1;
}

void TetrisModel::CheckGameOver() {
  if (CheckNEmptyRow(this->modelData_.field[0]))
    this->modelData_.pause = GameOver;
}

/* InitFrames ============================================================
 *{0, 0, 0, 0}  {0, 0, 0, 0}  {0, 0, 0, 0}  {0, 0, 0, 0}
 *{0, 1, 1, 0}  {0, 1, 1, 0}  {0, 1, 1, 0}  {0, 1, 1, 0}
 *{0, 1, 1, 0}  {0, 1, 1, 0}  {0, 1, 1, 0}  {0, 1, 1, 0}
 *{0, 0, 0, 0}  {0, 0, 0, 0}  {0, 0, 0, 0}  {0, 0, 0, 0}
 *
 *{0, 0, 0, 0}  {0, 0, 1, 0}  {0, 0, 0, 0}  {0, 1, 0, 0}
 *{1, 1, 1, 1}  {0, 0, 1, 0}  {0, 0, 0, 0}  {0, 1, 0, 0}
 *{0, 0, 0, 0}  {0, 0, 1, 0}  {1, 1, 1, 1}  {0, 1, 0, 0}
 *{0, 0, 0, 0}  {0, 0, 1, 0}  {0, 0, 0, 0}  {0, 1, 0, 0}
 *
 *{0, 0, 0, 0}  {0, 0, 0, 0}  {0, 1, 0, 0}  {0, 0, 0, 0}
 *{0, 1, 1, 0}  {0, 0, 1, 0}  {0, 1, 0, 0}  {0, 1, 1, 1}
 *{0, 0, 1, 0}  {1, 1, 1, 0}  {0, 1, 1, 0}  {0, 1, 0, 0}
 *{0, 0, 1, 0}  {0, 0, 0, 0}  {0, 0, 0, 0}  {0, 0, 0, 0}
 * ...
 */
const int TetrisModel::frames_[7][4][4][4] = {
    {{{0, 0, 0, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}},
     {{0, 0, 0, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}},
     {{0, 0, 0, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}},
     {{0, 0, 0, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}}},
    {{{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}},
     {{0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}},
     {{0, 0, 0, 0}, {0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}},
     {{0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}}},
    {{{0, 0, 0, 0}, {0, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}},
     {{0, 0, 0, 0}, {0, 0, 1, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}},
     {{0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}},
     {{0, 0, 0, 0}, {0, 1, 1, 1}, {0, 1, 0, 0}, {0, 0, 0, 0}}},
    {{{0, 0, 0, 0}, {0, 1, 1, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}},
     {{0, 0, 0, 0}, {1, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}},
     {{0, 0, 1, 0}, {0, 0, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}},
     {{0, 0, 0, 0}, {0, 1, 0, 0}, {0, 1, 1, 1}, {0, 0, 0, 0}}},
    {{{0, 0, 0, 0}, {0, 1, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}},
     {{0, 1, 0, 0}, {0, 1, 1, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}},
     {{0, 0, 0, 0}, {0, 1, 1, 1}, {0, 0, 1, 0}, {0, 0, 0, 0}},
     {{0, 0, 0, 0}, {0, 0, 1, 0}, {0, 1, 1, 0}, {0, 0, 1, 0}}},
    {{{0, 0, 0, 0}, {0, 1, 1, 0}, {0, 0, 1, 1}, {0, 0, 0, 0}},
     {{0, 0, 0, 0}, {0, 0, 1, 0}, {0, 1, 1, 0}, {0, 1, 0, 0}},
     {{0, 0, 0, 0}, {1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}},
     {{0, 0, 1, 0}, {0, 1, 1, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}}},
    {{{0, 0, 0, 0}, {0, 1, 1, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}},
     {{0, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}},
     {{0, 0, 0, 0}, {0, 0, 1, 1}, {0, 1, 1, 0}, {0, 0, 0, 0}},
     {{0, 0, 0, 0}, {0, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 1, 0}}}};

}  // namespace s21