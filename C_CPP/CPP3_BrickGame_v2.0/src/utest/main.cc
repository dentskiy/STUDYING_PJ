#include "unit_test.h"

int main(int argc, char** argv) {
  s21::FileManager FM;
  FM.SetFilename("Snake.txt");
  FM.SetSave(0);
  FM.SetFilename("Tetris.txt");
  FM.SetSave(0);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}