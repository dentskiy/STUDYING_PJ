#include "interfaces.h"

namespace s21 {
Model::Model() : modelData_{}, count_{}, level_{nullptr} {
  int**& field = modelData_.field;
  field = new int* [kHeight] {};
  for (int i{}; i < kHeight; i++) {
    field[i] = new int[kWidth]{};
  }
  modelData_.level = 1;
  modelData_.high_score = -1;
  modelData_.score = -1;
  modelData_.pause = -1;
  modelData_.speed = -1;
}

Model::~Model() {
  int**& field = modelData_.field;
  for (int i{}; field && i < kHeight; i++) {
    delete[] field[i];
  }
  delete[] field;
  field = nullptr;
}

void Model::FSMachine(UserAction_t signal, bool hold) {
  if (hold) {
    ModelMenu(signal);
  }
  if (modelData_.pause == ModelPlay) {
    if (count_ >= level_[modelData_.level - 1]) {
      if (!Move()) Clash();
      count_ = 0;
    } else {
      count_ += 1;
    }
  }
}

GameInfo_t& Model::getModelInfo() { return modelData_; }

void Model::ModelMenu(UserAction_t signal) {
  switch (this->modelData_.pause) {
    case ModelPlay:
      PlayMenu(signal);
      break;
    case ModelPause:
      if (signal == Action || signal == Start) {
        this->modelData_.pause = ModelPlay;
      }
      break;
    case GameOver:
      if (signal == Action || signal == Start) {
        ClearModel();
        InitModel();
        this->modelData_.pause = ModelPlay;
      }
      break;
  }
}

pos::pos(int i, int j) : x{i}, y{j} {}
pos::pos() : x{}, y{} {}
void pos::operator()(int i, int j) {
  x = i;
  y = j;
}

}  // namespace s21