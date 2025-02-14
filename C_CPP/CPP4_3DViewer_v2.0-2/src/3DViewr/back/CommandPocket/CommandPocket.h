#ifndef CPP4_3DVIEWER_V2_0_SRC_3DVIEWER_BACK_COMANDPOCKET_COMANDPOCKET_H
#define CPP4_3DVIEWER_V2_0_SRC_3DVIEWER_BACK_COMANDPOCKET_COMANDPOCKET_H

#include "../MoveStrategy/ObjMove.h"

namespace s21 {

class ModelCommand {
  std::unique_ptr<IMoveStrategy> strategy_;
  double val_;

 public:
  ModelCommand(IMoveStrategy* strategy, double val);
  ~ModelCommand() = default;
  void execute(ObjModel& model);
};

class ICommandFactory {
 public:
  virtual ModelCommand* createCommand(double val) = 0;
  virtual ~ICommandFactory() = default;
};

class LineMoveXFactory : public ICommandFactory {
 public:
  ModelCommand* createCommand(double val) override;
};

class LineMoveYFactory : public ICommandFactory {
 public:
  ModelCommand* createCommand(double val) override;
};

class LineMoveZFactory : public ICommandFactory {
 public:
  ModelCommand* createCommand(double val) override;
};

class CircularMoveXFactory : public ICommandFactory {
 public:
  ModelCommand* createCommand(double val) override;
};

class CircularMoveYFactory : public ICommandFactory {
 public:
  ModelCommand* createCommand(double val) override;
};

class CircularMoveZFactory : public ICommandFactory {
 public:
  ModelCommand* createCommand(double val) override;
};

class ScaleMoveFactory : public ICommandFactory {
 public:
  ModelCommand* createCommand(double val) override;
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_SRC_3DVIEWER_BACK_COMANDPOCKET_COMANDPOCKET_H