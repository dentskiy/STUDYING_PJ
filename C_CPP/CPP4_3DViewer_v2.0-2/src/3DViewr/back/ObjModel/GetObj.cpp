#include <stdexcept>

#include "ObjModel.h"

namespace s21 {
double& ObjModel::getVertexX(size_t verticesNum) {
  return vertices[verticesNum * 3];
}

double& ObjModel::getVertexY(size_t verticesNum) {
  return vertices[verticesNum * 3 + 1];
}

double& ObjModel::getVertexZ(size_t verticesNum) {
  return vertices[verticesNum * 3 + 2];
}

const size_t& ObjModel::getFaces(size_t fasesNum) { return faces[fasesNum]; }

const size_t& ObjModel::getVertexSize() noexcept { return v_count; }

const size_t& ObjModel::getFacesSize() noexcept { return f_count; }

}  // namespace s21