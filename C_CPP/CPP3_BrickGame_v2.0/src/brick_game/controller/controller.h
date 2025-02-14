#ifndef CPP3_BRICKGAME_SRC_BRICK_GAME_CONTROLLER_CONTROLLER_H
#define CPP3_BRICKGAME_SRC_BRICK_GAME_CONTROLLER_CONTROLLER_H

#include "../interfaces/interfaces.h"

namespace s21 {

class Controller {
 private:
  Model* game_;

 public:
  Controller(Model*&& newGame);
  ~Controller();

  void userInput(UserAction_t action, bool hold);
  GameInfo_t updateCurrentState();
  void ChangeModel(Model*&& Game);
};

}  // namespace s21

#endif  // CPP3_BRICKGAME_SRC_BRICK_GAME_CONTROLLER_CONTROLLER_H