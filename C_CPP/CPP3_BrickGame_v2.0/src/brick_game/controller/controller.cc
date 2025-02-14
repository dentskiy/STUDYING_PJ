#include "controller.h"

namespace s21 {

Controller::Controller(Model*&& newGame) : game_{newGame} { newGame = nullptr; }
Controller::~Controller() { delete game_; }

void Controller::userInput(UserAction_t action, bool hold) {
  game_->FSMachine(action, hold);
}
GameInfo_t Controller::updateCurrentState() { return game_->getModelInfo(); }

void Controller::ChangeModel(Model*&& Game) {
  if (game_ == Game) return;
  delete game_;
  game_ = Game;
  Game = nullptr;
}

}  // namespace s21