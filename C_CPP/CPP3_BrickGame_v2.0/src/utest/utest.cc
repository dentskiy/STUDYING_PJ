#include "unit_test.h"

TEST(SnakeTests, FirstInit) {
  s21::SnakeModel* game = new s21::SnakeModel();
  s21::GameInfo_t table = game->getModelInfo();
  ASSERT_EQ(table.level, 1);
  ASSERT_EQ(table.next, nullptr);
  ASSERT_EQ(table.pause, s21::ModelPause);
  ASSERT_EQ(table.score, 0);
  ASSERT_EQ(table.speed, -1);
  for (int i{}; i < s21::kHeight; i++) {
    for (int j{}; j < s21::kWidth; j++) {
      ASSERT_TRUE(table.field[i][j] == s21::kStaticCell ||
                  table.field[i][j] == s21::kMoveCell ||
                  table.field[i][j] == s21::kEmptyCell);
    }
  }
  delete game;
};

TEST(SnakeTests, UsingParentPointer) {
  s21::Model* game = new s21::SnakeModel();
  s21::GameInfo_t table = game->getModelInfo();
  ASSERT_EQ(table.level, 1);
  ASSERT_EQ(table.next, nullptr);
  ASSERT_EQ(table.pause, s21::ModelPause);
  ASSERT_EQ(table.score, 0);
  ASSERT_EQ(table.speed, -1);
  for (int i{}; i < s21::kHeight; i++) {
    for (int j{}; j < s21::kWidth; j++) {
      ASSERT_TRUE(table.field[i][j] == s21::kStaticCell ||
                  table.field[i][j] == s21::kMoveCell ||
                  table.field[i][j] == s21::kEmptyCell);
    }
  }
  delete game;
}

TEST(SnakeTests, MoveTest) {
  s21::Model* game = new s21::SnakeModel();
  game->FSMachine(s21::Action, true);
  s21::GameInfo_t& data = game->getModelInfo();
  ASSERT_EQ(data.pause, s21::ModelPlay);
  while (data.pause != s21::GameOver) {
    game->FSMachine({}, false);
  }
  ASSERT_EQ(data.pause, s21::GameOver);
  delete game;
}

TEST(SnakeTests, WinCaseTest) {
  s21::Model* game = new s21::SnakeModel();
  game->FSMachine(s21::Action, true);
  s21::GameInfo_t& data = game->getModelInfo();
  ASSERT_EQ(data.pause, s21::ModelPlay);
  for (int i{4}; i < s21::kWidth; i++) game->FSMachine(s21::Action, true);
  game->FSMachine(s21::Down, true);
  game->FSMachine(s21::Action, true);
  while (data.pause != s21::GameOver) {
    for (int i{}; i < s21::kWidth; i += 2) {
      for (int j{3}; j < s21::kHeight; j++) {
        game->FSMachine(s21::Action, !(bool)data.pause);
      }
      game->FSMachine(s21::Left, true);
      game->FSMachine(s21::Up, true);
      for (int j{3}; j < s21::kHeight; j++) {
        game->FSMachine(s21::Action, !(bool)data.pause);
      }
      if (i != s21::kWidth - 2) {
        game->FSMachine(s21::Left, true);
        game->FSMachine(s21::Down, true);
      }
    }
    game->FSMachine(s21::Action, !(bool)data.pause);
    game->FSMachine(s21::Right, true);
    for (int i{2}; i < s21::kWidth; i++) {
      game->FSMachine(s21::Action, !(bool)data.pause);
    }
    game->FSMachine(s21::Down, true);
    game->FSMachine(s21::Action, !(bool)data.pause);
  }
  ASSERT_EQ(data.score, s21::kCellCount - 4);
  ASSERT_EQ(data.pause, s21::GameOver);
  for (int i{}; i < s21::kHeight; i++) {
    for (int j{}; j < s21::kWidth; j++) {
      ASSERT_EQ(data.field[i][j], s21::kMoveCell);
    }
  }
  delete game;
}

TEST(SnakeTests, CheckSaveTest) {
  s21::Model* game = new s21::SnakeModel();
  ASSERT_EQ(game->getModelInfo().high_score, s21::kCellCount - 4);
  delete game;
}

TEST(TetrisTests, FirstInit) {
  s21::TetrisModel* game = new s21::TetrisModel();
  s21::GameInfo_t table = game->getModelInfo();
  ASSERT_EQ(table.level, 1);
  ASSERT_NE(table.next, nullptr);
  ASSERT_EQ(table.pause, s21::ModelPause);
  ASSERT_EQ(table.score, 0);
  ASSERT_EQ(table.speed, -1);
  for (int i{3}; i < s21::kHeight; i++) {
    for (int j{}; j < s21::kWidth; j++) {
      ASSERT_TRUE(table.field[i][j] == s21::kEmptyCell);
    }
  }
  delete game;
};

TEST(TetrisTests, UsingParentPointer) {
  s21::Model* game = new s21::TetrisModel();
  s21::GameInfo_t table = game->getModelInfo();
  ASSERT_EQ(table.level, 1);
  ASSERT_NE(table.next, nullptr);
  ASSERT_EQ(table.pause, s21::ModelPause);
  ASSERT_EQ(table.score, 0);
  ASSERT_EQ(table.speed, -1);
  for (int i{3}; i < s21::kHeight; i++) {
    for (int j{}; j < s21::kWidth; j++) {
      ASSERT_TRUE(table.field[i][j] == s21::kEmptyCell);
    }
  }
  delete game;
}

TEST(TetrisTests, DefaultMoveTest) {
  s21::Model* game = new s21::TetrisModel();
  game->FSMachine(s21::Action, true);
  s21::GameInfo_t& data = game->getModelInfo();
  ASSERT_EQ(data.pause, s21::ModelPlay);
  while (data.pause != s21::GameOver) {
    game->FSMachine({}, false);
  }
  ASSERT_EQ(data.pause, s21::GameOver);
  delete game;
}

TEST(TetrisTests, ManualMoveTest1) {
  bool flag{false};
  s21::Model* game = new s21::TetrisModel();
  game->FSMachine(s21::Action, true);
  s21::GameInfo_t& data = game->getModelInfo();
  ASSERT_EQ(data.pause, s21::ModelPlay);
  while (data.pause != s21::GameOver) {
    game->FSMachine(s21::Right, true);
  }
  for (int i{0}; i < s21::kHeight && !flag; i++) {
    flag = data.field[i][s21::kWidth - 1] == s21::kStaticCell;
  }
  ASSERT_TRUE(flag);
  ASSERT_EQ(data.pause, s21::GameOver);
  delete game;
}

TEST(TetrisTests, ManualMoveTest2) {
  bool flag{false};
  s21::Model* game = new s21::TetrisModel();
  game->FSMachine(s21::Action, true);
  s21::GameInfo_t& data = game->getModelInfo();
  ASSERT_EQ(data.pause, s21::ModelPlay);
  while (data.pause != s21::GameOver) {
    game->FSMachine(s21::Left, true);
    game->FSMachine(s21::Down, true);
  }
  for (int i{0}; i < s21::kHeight && !flag; i++) {
    flag = data.field[i][0] == s21::kStaticCell;
  }
  ASSERT_TRUE(flag);
  ASSERT_EQ(data.pause, s21::GameOver);
  delete game;
}

TEST(TetrisTests, ManualMoveTest3) {
  s21::Model* game = new s21::TetrisModel();
  game->FSMachine(s21::Action, true);
  s21::GameInfo_t& data = game->getModelInfo();
  ASSERT_EQ(data.pause, s21::ModelPlay);
  while (data.pause != s21::GameOver) {
    game->FSMachine(s21::Up, true);
  }
  ASSERT_EQ(data.pause, s21::GameOver);
  game->FSMachine(s21::Action, true);
  ASSERT_EQ(data.pause, s21::ModelPlay);
  game->FSMachine(s21::Pause, true);
  ASSERT_EQ(data.pause, s21::ModelPause);
  game->FSMachine(s21::Action, true);
  game->FSMachine(s21::Terminate, true);
  ASSERT_EQ(data.pause, s21::GameOver);
  delete game;
}

TEST(TetrisTests, ScoreAndSaves) {
  int myScore = 9999;
  s21::Model* game = new s21::TetrisModel();
  game->FSMachine(s21::Action, true);
  s21::GameInfo_t& data = game->getModelInfo();
  ASSERT_EQ(data.pause, s21::ModelPlay);
  ASSERT_EQ(data.high_score, 0);
  game->FSMachine(s21::Action, true);
  data.score = myScore;
  game->FSMachine(s21::Terminate, true);
  ASSERT_EQ(data.pause, s21::GameOver);
  game->FSMachine(s21::Action, true);
  ASSERT_EQ(data.high_score, myScore);
  delete game;
}

TEST(ControllerTests, InitGame) {
  s21::Controller ctrl1(new s21::TetrisModel());
  s21::Controller ctrl2(new s21::SnakeModel());
  s21::GameInfo_t data = ctrl1.updateCurrentState();
  ASSERT_EQ(data.level, 1);
  ASSERT_FALSE(!data.next);
  ASSERT_FALSE(!data.field);
  ASSERT_EQ(data.pause, s21::ModelPause);
  ASSERT_EQ(data.speed, -1);
  ASSERT_EQ(data.score, 0);
  data = ctrl2.updateCurrentState();
  ASSERT_EQ(data.level, 1);
  ASSERT_TRUE(!data.next);
  ASSERT_FALSE(!data.field);
  ASSERT_EQ(data.pause, s21::ModelPause);
  ASSERT_EQ(data.speed, -1);
  ASSERT_EQ(data.score, 0);
}

TEST(ControllerTests, SwitchModelTest) {
  s21::Controller ctrl(new s21::TetrisModel());
  s21::GameInfo_t data = ctrl.updateCurrentState();
  ASSERT_EQ(data.level, 1);
  ASSERT_FALSE(!data.next);
  ASSERT_FALSE(!data.field);
  ASSERT_EQ(data.pause, s21::ModelPause);
  ASSERT_EQ(data.speed, -1);
  ASSERT_EQ(data.score, 0);
  ctrl.ChangeModel(new s21::SnakeModel());
  data = ctrl.updateCurrentState();
  ASSERT_EQ(data.level, 1);
  ASSERT_TRUE(!data.next);
  ASSERT_FALSE(!data.field);
  ASSERT_EQ(data.pause, s21::ModelPause);
  ASSERT_EQ(data.speed, -1);
  ASSERT_EQ(data.score, 0);
}

TEST(ControllerTests, InputTest) {
  s21::Controller ctrl(new s21::TetrisModel());
  s21::GameInfo_t data = ctrl.updateCurrentState();
  ASSERT_EQ(data.pause, s21::ModelPause);
  ctrl.userInput(s21::Action, true);
  data = ctrl.updateCurrentState();
  ASSERT_EQ(data.pause, s21::ModelPlay);
  while (data.pause != s21::GameOver) {
    ctrl.userInput(s21::Action, true);
    data = ctrl.updateCurrentState();
  }
  ASSERT_EQ(data.pause, s21::GameOver);
  ctrl.userInput(s21::Action, true);
  data = ctrl.updateCurrentState();
  ASSERT_EQ(data.pause, s21::ModelPlay);
  ctrl.userInput(s21::Pause, true);
  data = ctrl.updateCurrentState();
  ASSERT_EQ(data.pause, s21::ModelPause);
}