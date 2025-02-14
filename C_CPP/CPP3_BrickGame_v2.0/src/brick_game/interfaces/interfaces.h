#ifndef CPP3_BRICKGAME_SRC_BRICK_GAME_INTERFACES_INTERFACES_H
#define CPP3_BRICKGAME_SRC_BRICK_GAME_INTERFACES_INTERFACES_H

#include "../utils/utils.h"

namespace s21 {

enum ModelStatus_t { ModelPlay, ModelPause, GameOver };

class Model {
 protected:
  GameInfo_t modelData_;
  int count_;
  const int *level_;
  FileManager fManager_;

 public:
  Model();
  virtual ~Model();

  void FSMachine(UserAction_t signal, bool hold);
  GameInfo_t &getModelInfo();

 protected:
  void ModelMenu(UserAction_t signal);
  virtual void PlayMenu(UserAction_t signal) = 0;
  virtual bool Move() = 0;
  virtual void InitModel() = 0;
  virtual void ClearModel() = 0;
  virtual void Clash() = 0;
};

struct pos {
  int x;
  int y;

  pos(int i, int j);
  pos();
  ~pos() = default;
  void operator()(int i, int j);
};

}  // namespace s21

#endif  // CPP3_BRICKGAME_SRC_BRICK_GAME_INTERFACES_INTERFACES_H