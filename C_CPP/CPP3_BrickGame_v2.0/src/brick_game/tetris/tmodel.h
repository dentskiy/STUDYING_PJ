#ifndef CPP3_BRICKGAME_SRC_BRICK_GAME_TETRIS_TMODEL_H
#define CPP3_BRICKGAME_SRC_BRICK_GAME_TETRIS_TMODEL_H

#include "../interfaces/interfaces.h"

namespace s21 {

class TetrisModel : public Model {
 public:
  TetrisModel(const char* filename = "Tetris.txt");
  ~TetrisModel();

 private:
  void InitModel() override;
  void ClearModel() override;
  bool Move() override;
  void PlayMenu(UserAction_t signal) override;
  void Clash() override;

  void PrintFrame(int** map, pos position, int num, int rot);
  void ClearFrame(int** map, pos position);
  bool CheckMove();
  void FixMovedCell();
  void RotateUp();
  void RotateDown();

  bool CheckBag();
  void SpawnObject();
  void UpdateScore();
  void CheckGameOver();

  pos fPosition_;
  int nFrame_;
  int nFrameNext_;
  int rFrame_;
  bool tBag_[7];

 public:
  static const int frames_[7][4][4][4];
};

}  // namespace s21

#endif  // CPP3_BRICKGAME_SRC_BRICK_GAME_TETRIS_TMODEL_H