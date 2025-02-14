#include "CommandPocket.h"

namespace s21 {

ModelCommand::ModelCommand(IMoveStrategy *strategy, double val) {
  strategy_ = std::unique_ptr<IMoveStrategy>(strategy);
  val_ = val;
}

void ModelCommand::execute(ObjModel &model) { strategy_->move(model, val_); }

ModelCommand *LineMoveXFactory::createCommand(double val) {
  return new ModelCommand(new LineMoveX, val);
}

ModelCommand *LineMoveYFactory::createCommand(double val) {
  return new ModelCommand(new LineMoveY, val);
}

ModelCommand *LineMoveZFactory::createCommand(double val) {
  return new ModelCommand(new LineMoveZ, val);
}

ModelCommand *CircularMoveXFactory::createCommand(double val) {
  return new ModelCommand(new CircularMoveX, val);
}

ModelCommand *CircularMoveYFactory::createCommand(double val) {
  return new ModelCommand(new CircularMoveY, val);
}

ModelCommand *CircularMoveZFactory::createCommand(double val) {
  return new ModelCommand(new CircularMoveZ, val);
}

ModelCommand *ScaleMoveFactory::createCommand(double val) {
  return new ModelCommand(new ScaleMove, val);
}

}  // namespace s21