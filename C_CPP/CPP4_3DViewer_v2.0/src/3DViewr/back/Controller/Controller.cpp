#include "Controller.h"

namespace s21 {

Faced::Faced(ObjModel* model) {
  model_ = std::unique_ptr<ObjModel>(model ?: new ObjModel());
}

const double& Faced::getModelX(size_t num) { return model_->getVertexX(num); }
const double& Faced::getModelY(size_t num) { return model_->getVertexY(num); }
const double& Faced::getModelZ(size_t num) { return model_->getVertexZ(num); }
const size_t& Faced::getModelFaces(size_t num) { return model_->getFaces(num); }
const size_t& Faced::getModelVertexSize() { return model_->getVertexSize(); }
const size_t& Faced::getModelFacesSize() { return model_->getFacesSize(); }

void Faced::executor(ModelCommand& command) { command.execute(*model_); }

void Faced::setNewObject(std::string fileName) { model_->readFile(fileName); }

}  // namespace s21