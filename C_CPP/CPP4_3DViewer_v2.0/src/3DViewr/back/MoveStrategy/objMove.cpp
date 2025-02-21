#include "ObjMove.h"

#include <cmath>
#include <stdexcept>

namespace s21 {

void LineMoveX::move(ObjModel &data, double val) {
  for (size_t i = 0; i < data.getVertexSize(); i++) {
    data.getVertexX(i) += val;
  }
}

void LineMoveY::move(ObjModel &data, double val) {
  for (size_t i = 0; i < data.getVertexSize(); i++) {
    data.getVertexY(i) += val;
  }
}

void LineMoveZ::move(ObjModel &data, double val) {
  for (size_t i = 0; i < data.getVertexSize(); i++) {
    data.getVertexZ(i) += val;
  }
}

void CircularMoveX::move(ObjModel &data, double val) {
  for (size_t i = 0; i < data.getVertexSize(); i++) {
    double angle_in_rad = val * DEGREES_TO_RADIANS;
    double cos_a = cos(angle_in_rad);
    double sin_a = sin(angle_in_rad);

    double y = data.getVertexY(i);
    double z = data.getVertexZ(i);

    data.getVertexY(i) = y * cos_a + z * sin_a;
    data.getVertexZ(i) = -y * sin_a + z * cos_a;
  }
}

void CircularMoveY::move(ObjModel &data, double val) {
  for (size_t i = 0; i < data.getVertexSize(); i++) {
    double angle_in_rad = val * DEGREES_TO_RADIANS;
    double cos_a = cos(angle_in_rad);
    double sin_a = sin(angle_in_rad);

    double x = data.getVertexX(i);
    double z = data.getVertexZ(i);

    data.getVertexX(i) = x * cos_a + z * sin_a;
    data.getVertexZ(i) = -x * sin_a + z * cos_a;
  }
}

void CircularMoveZ::move(ObjModel &data, double val) {
  for (size_t i = 0; i < data.getVertexSize(); i++) {
    double angle_in_rad = val * DEGREES_TO_RADIANS;
    double cos_a = cos(angle_in_rad);
    double sin_a = sin(angle_in_rad);

    double x = data.getVertexX(i);
    double y = data.getVertexY(i);

    data.getVertexX(i) = x * cos_a + y * sin_a;
    data.getVertexY(i) = -x * sin_a + y * cos_a;
  }
}

void ScaleMove::move(ObjModel &data, double val) {
  if (val <= -100.)
    throw(std::domain_error("Scale: Attempt to turn the object inside out"));
  for (size_t i = 0; i < data.getVertexSize(); i++) {
    data.getVertexX(i) *= 1. + val / 100.;
    data.getVertexY(i) *= 1. + val / 100.;
    data.getVertexZ(i) *= 1. + val / 100.;
  }
}
}  // namespace s21