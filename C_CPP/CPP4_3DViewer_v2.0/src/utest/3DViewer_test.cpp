#include <iostream>

#include "unit_test.h"

using namespace s21;

TEST(OBJ_MODEL_TESTS, InitTest2) {
  ObjModel *model = new ObjModel();
  EXPECT_EQ(model->getFacesSize(), 0);
  EXPECT_EQ(model->getVertexSize(), 0);
  delete model;
}

TEST(OBJ_MODEL_TESTS, FileReadTest) {
  auto model = std::make_unique<ObjModel>();
  std::string testFile("utest/TestObject/cube_obj.test");
  try {
    model->readFile(testFile);
    EXPECT_EQ(model->getFacesSize(), 48);
    EXPECT_EQ(model->getVertexSize(), 8);
    EXPECT_EQ(model->getFaces(0), 1);
    EXPECT_EQ(model->getVertexX(0), 1.);
    EXPECT_EQ(model->getVertexY(0), -1.);
    EXPECT_EQ(model->getVertexZ(0), -1.);
  } catch (std::exception &out) {
    std::cerr << out.what() << std::endl;
  }
}

TEST(OBJ_MODEL_TESTS, ObjLineMoveTest) {
  auto model = std::make_unique<ObjModel>();
  std::string testFile("utest/TestObject/cube_obj.test");
  std::unique_ptr<s21::IMoveStrategy> cmd;
  double curretn{};
  try {
    model->readFile(testFile);
    curretn = model->getVertexX(0);
    cmd = std::make_unique<s21::LineMoveX>();
    cmd->move(*model, 1.);
    EXPECT_NEAR(model->getVertexX(0), curretn + 1., 1E-7);
    curretn = model->getVertexY(0);
    cmd = std::make_unique<s21::LineMoveY>();
    cmd->move(*model, 1.);
    EXPECT_NEAR(model->getVertexY(0), curretn + 1., 1E-7);
    curretn = model->getVertexZ(0);
    cmd = std::make_unique<s21::LineMoveZ>();
    cmd->move(*model, 1.);
    EXPECT_NEAR(model->getVertexZ(0), curretn + 1., 1E-7);
  } catch (std::exception &out) {
    std::cerr << out.what() << std::endl;
  }
}

TEST(OBJ_MODEL_TESTS, ObjCircularMoveTest) {
  auto model = std::make_unique<ObjModel>();
  std::string testFile("utest/TestObject/cube_obj.test");
  std::unique_ptr<s21::IMoveStrategy> cmd;
  double curretn[2]{};
  try {
    model->readFile(testFile);
    curretn[0] = model->getVertexY(0);
    curretn[1] = model->getVertexZ(0);
    cmd = std::make_unique<s21::CircularMoveX>();
    cmd->move(*model, 180.);
    EXPECT_NEAR(model->getVertexY(0), -curretn[0], 1E-7);
    EXPECT_NEAR(model->getVertexZ(0), -curretn[1], 1E-7);
    curretn[0] = model->getVertexX(0);
    curretn[1] = model->getVertexZ(0);
    cmd = std::make_unique<s21::CircularMoveY>();
    cmd->move(*model, 180.);
    EXPECT_NEAR(model->getVertexX(0), -curretn[0], 1E-7);
    EXPECT_NEAR(model->getVertexZ(0), -curretn[1], 1E-7);
    curretn[0] = model->getVertexY(0);
    curretn[1] = model->getVertexX(0);
    cmd = std::make_unique<s21::CircularMoveZ>();
    cmd->move(*model, 180.);
    EXPECT_NEAR(model->getVertexY(0), -curretn[0], 1E-7);
    EXPECT_NEAR(model->getVertexX(0), -curretn[1], 1E-7);
  } catch (std::exception &out) {
    std::cerr << out.what() << std::endl;
  }
}

TEST(OBJ_MODEL_TESTS, ObjScaleMoveTest) {
  auto model = std::make_unique<ObjModel>();
  std::string testFile("utest/TestObject/cube_obj.test");
  std::unique_ptr<s21::IMoveStrategy> cmd;
  double curretn[3]{};
  try {
    model->readFile(testFile);
    cmd = std::make_unique<s21::ScaleMove>();
    for (size_t i{}; i < model->getVertexSize(); i++) {
      curretn[0] = model->getVertexX(i);
      curretn[1] = model->getVertexY(i);
      curretn[2] = model->getVertexZ(i);
      cmd->move(*model, 25.);
      EXPECT_NEAR(model->getVertexX(i), curretn[0] * 1.25, 1E-7);
      EXPECT_NEAR(model->getVertexY(i), curretn[1] * 1.25, 1E-7);
      EXPECT_NEAR(model->getVertexZ(i), curretn[2] * 1.25, 1E-7);
    }
  } catch (std::exception &out) {
    std::cerr << out.what() << std::endl;
  }
}

TEST(OBJ_MODEL_TESTS, ObjScaleThrowTest) {
  auto model = std::make_unique<ObjModel>();
  std::string testFile("utest/TestObject/cube_obj.test");
  std::unique_ptr<s21::IMoveStrategy> cmd;
  try {
    model->readFile(testFile);
    cmd = std::make_unique<s21::ScaleMove>();
    EXPECT_ANY_THROW(cmd->move(*model, -200.));
  } catch (std::exception &out) {
    std::cerr << out.what() << std::endl;
  }
}

TEST(COMMAND_POCKET_TESTS, ExecuteCommandTest) {
  auto model = std::make_unique<ObjModel>();
  std::string testFile("utest/TestObject/cube_obj.test");
  model->readFile(testFile);

  std::unique_ptr<ICommandFactory> factory;
  std::unique_ptr<ModelCommand> command;

  // Test LineMoveX
  factory = std::make_unique<LineMoveXFactory>();
  command.reset(factory->createCommand(1.0));
  double initialX = model->getVertexX(0);
  command->execute(*model);
  EXPECT_NEAR(model->getVertexX(0), initialX + 1.0, 1E-7);

  // Test LineMoveY
  factory = std::make_unique<LineMoveYFactory>();
  command.reset(factory->createCommand(1.0));
  double initialY = model->getVertexY(0);
  command->execute(*model);
  EXPECT_NEAR(model->getVertexY(0), initialY + 1.0, 1E-7);

  // Test LineMoveZ
  factory = std::make_unique<LineMoveZFactory>();
  command.reset(factory->createCommand(1.0));
  double initialZ = model->getVertexZ(0);
  command->execute(*model);
  EXPECT_NEAR(model->getVertexZ(0), initialZ + 1.0, 1E-7);

  // Test CircularMoveX
  factory = std::make_unique<CircularMoveXFactory>();
  command.reset(factory->createCommand(90.0));
  double initialY_circ = model->getVertexY(0);
  double initialZ_circ = model->getVertexZ(0);
  command->execute(*model);
  EXPECT_NEAR(model->getVertexY(0), initialZ_circ, 1E-7);
  EXPECT_NEAR(model->getVertexZ(0), -initialY_circ, 1E-7);

  // Test ScaleMove
  factory = std::make_unique<ScaleMoveFactory>();
  command.reset(factory->createCommand(25.0));
  double initialX_scale = model->getVertexX(0);
  double initialY_scale = model->getVertexY(0);
  double initialZ_scale = model->getVertexZ(0);
  command->execute(*model);
  EXPECT_NEAR(model->getVertexX(0), initialX_scale * 1.25, 1E-7);
  EXPECT_NEAR(model->getVertexY(0), initialY_scale * 1.25, 1E-7);
  EXPECT_NEAR(model->getVertexZ(0), initialZ_scale * 1.25, 1E-7);
}

TEST(FACED_TESTS, InitTest) {
  Faced *faced = new Faced();
  EXPECT_EQ(faced->getModelVertexSize(), 0);
  EXPECT_EQ(faced->getModelFacesSize(), 0);
  delete faced;
}

TEST(FACED_TESTS, SetNewObjectTest) {
  auto faced = std::make_unique<Faced>();
  std::string testFile("utest/TestObject/cube_obj.test");
  faced->setNewObject(testFile);
  EXPECT_EQ(faced->getModelVertexSize(), 8);
  EXPECT_EQ(faced->getModelFacesSize(), 48);
  EXPECT_EQ(faced->getModelX(0), 1.0);
  EXPECT_EQ(faced->getModelY(0), -1.0);
  EXPECT_EQ(faced->getModelZ(0), -1.0);
}

TEST(FACED_TESTS, ExecutorTest) {
  auto faced = std::make_unique<Faced>();
  std::string testFile("utest/TestObject/cube_obj.test");
  faced->setNewObject(testFile);

  std::unique_ptr<ICommandFactory> factory;
  std::unique_ptr<ModelCommand> command;

  // Test LineMoveX
  factory = std::make_unique<LineMoveXFactory>();
  command.reset(factory->createCommand(1.0));
  double initialX = faced->getModelX(0);
  faced->executor(*command);
  EXPECT_NEAR(faced->getModelX(0), initialX + 1.0, 1E-7);

  // Test CircularMoveY
  factory = std::make_unique<CircularMoveYFactory>();
  command.reset(factory->createCommand(90.0));
  double initialX_circ = faced->getModelX(0);
  double initialZ_circ = faced->getModelZ(0);
  faced->executor(*command);
  EXPECT_NEAR(faced->getModelX(0), initialZ_circ, 1E-7);
  EXPECT_NEAR(faced->getModelZ(0), -initialX_circ, 1E-7);
}