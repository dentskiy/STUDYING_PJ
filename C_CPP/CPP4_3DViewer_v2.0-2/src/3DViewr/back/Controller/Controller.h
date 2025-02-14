#ifndef CPP4_3DVIEWER_V2_0_SRC_3DVIEWER_BACK_CONTROLLER_CONTROLLER_H
#define CPP4_3DVIEWER_V2_0_SRC_3DVIEWER_BACK_CONTROLLER_CONTROLLER_H

#include "../CommandPocket/CommandPocket.h"
namespace s21 {

class Faced {
  std::unique_ptr<ObjModel> model_;

 public:
  Faced(ObjModel* model = nullptr);
  ~Faced() = default;
  const double& getModelX(size_t num);
  const double& getModelY(size_t num);
  const double& getModelZ(size_t num);
  const size_t& getModelFaces(size_t num);
  const size_t& getModelVertexSize();
  const size_t& getModelFacesSize();

  void executor(ModelCommand& command);
  void setNewObject(std::string fileName);
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_SRC_3DVIEWER_BACK_CONTROLLER_CONTROLLER_H