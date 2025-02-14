#ifndef CPP3_BRICKGAME_SRC_BRICK_GAME_SNAKE_SMODEL_H
#define CPP3_BRICKGAME_SRC_BRICK_GAME_SNAKE_SMODEL_H

#include <queue>

#include "../interfaces/interfaces.h"

namespace s21 {

class SnakeModel : public Model {
  std::queue<typename s21::pos> snake_;
  pos sFace_;

 public:
  SnakeModel(const char* filename = "Snake.txt");
  ~SnakeModel();

 private:
  void InitModel() override;  // add read high score
  void ClearModel() override;
  bool Move() override;
  void PlayMenu(UserAction_t signal) override;
  void Clash() override;  // add write high score

  void EatApple();
  void SnakeMove();
  void SpawnApple();
  bool CheckCell(int x, int y);
};

}  // namespace s21

#endif  // CPP3_BRICKGAME_SRC_BRICK_GAME_SNAKE_MODEL_H