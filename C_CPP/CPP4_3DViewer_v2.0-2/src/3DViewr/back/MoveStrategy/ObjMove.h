#ifndef CPP4_3DVIEWER_V2_0_SRC_3DVIEWER_BACK_MOVESTRATEGY_OBJMOVE_H
#define CPP4_3DVIEWER_V2_0_SRC_3DVIEWER_BACK_MOVESTRATEGY_OBJMOVE_H

#include "../ObjModel/ObjModel.h"

namespace s21 {

class IMoveStrategy {
 public:
  virtual void move(ObjModel &data, double val) = 0;
  virtual ~IMoveStrategy() = default;
};

class LineMoveX : public IMoveStrategy {
 public:
  void move(ObjModel &data, double val) override;
};

class LineMoveY : public IMoveStrategy {
 public:
  void move(ObjModel &data, double val) override;
};

class LineMoveZ : public IMoveStrategy {
 public:
  void move(ObjModel &data, double val) override;
};

class CircularMoveX : public IMoveStrategy {
 public:
  void move(ObjModel &data, double val) override;
};

class CircularMoveY : public IMoveStrategy {
 public:
  void move(ObjModel &data, double val) override;
};

class CircularMoveZ : public IMoveStrategy {
 public:
  void move(ObjModel &data, double val) override;
};

class ScaleMove : public IMoveStrategy {
 public:
  void move(ObjModel &data, double val) override;
};
}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_SRC_3DVIEWER_BACK_MOVESTRATEGY_OBJMOVE_H