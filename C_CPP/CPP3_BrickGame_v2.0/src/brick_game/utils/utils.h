#ifndef CPP3_BRICKGAME_SRC_BRICK_GAME_UTILS_FILEMANAGER_H
#define CPP3_BRICKGAME_SRC_BRICK_GAME_UTILS_FILEMANAGER_H

namespace s21 {

constexpr const int kWidth = 10;
constexpr const int kHeight = 20;
constexpr const int kCellCount = 200;
constexpr const int kEmptyCell = 0;
constexpr const int kMoveCell = 1;
constexpr const int kStaticCell = 2;

typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;

typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

class FileManager {
  char fname_[300];

 public:
  FileManager();
  ~FileManager() = default;

  bool SetFilename(const char *fname);
  void SetSave(int score);
  int GetSave();
};

}  // namespace s21

#endif  // CPP3_BRICKGAME_SRC_BRICK_GAME_UTILS_FILEMANAGER_H