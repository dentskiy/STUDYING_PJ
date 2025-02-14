#ifndef CPP4_3DVIEWER_V2_0_SRC_3DVIEWER_BACK_OBJMODEL_OBJMODEL_H
#define CPP4_3DVIEWER_V2_0_SRC_3DVIEWER_BACK_OBJMODEL_OBJMODEL_H

#include <memory>
#include <string>
#include <vector>

enum Result { OK, ERROR };

#define DEGREES_TO_RADIANS M_PI / 180.0

namespace s21 {

enum class axes { kAxeX, kAxeY, kAxeZ };

class DotObjData {
 public:
  std::vector<double> vertices;
  std::vector<size_t> faces;
  size_t v_count;
  size_t f_count;

  DotObjData() : vertices{}, faces{}, v_count{}, f_count{} {};
  ~DotObjData() = default;
};

class ObjReader : protected DotObjData {
 public:
  ObjReader() = default;
  ~ObjReader() = default;
  void readFile(std::string& fileName);

 private:
  void objClear() noexcept;
  void counterVertexFaces(std::ifstream& filestream);
  void writeObjectData(std::ifstream& filestream);
};

class ObjModel : public ObjReader {
 public:
  const size_t& getVertexSize() noexcept;
  const size_t& getFacesSize() noexcept;

  double& getVertexX(size_t verticesNum);
  double& getVertexY(size_t verticesNum);
  double& getVertexZ(size_t verticesNum);

  const size_t& getFaces(size_t fasesNum);
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_SRC_3DVIEWER_BACK_OBJMODEL_OBJMODEL_H