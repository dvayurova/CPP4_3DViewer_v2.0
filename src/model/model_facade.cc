#include "model_facade.h"

#include <string>
namespace s21 {
void Model::ChangeModel(std::string action, double value, int axis) {
  transform_->value = value;
  transform_->axis = axis;

  if (action == "rotate") {
    transformation_.Rotate(*object_, *transform_);
  } else if (action == "scale" && value != 0) {
    transformation_.Scale(*object_, *transform_);
  } else if (action == "move") {
    transformation_.Translate(*object_, *transform_);
  }
}

void Model::Clear() {
  transform_->prev_coor_ = {0};
  transform_->prev_angle_x = 0;
  transform_->prev_angle_y = 0;
  transform_->prev_angle_z = 0;
  object_->count_edges_ = 0;
  object_->count_facets_ = 0;
  object_->count_vertex_ = 0;
  if (!object_->vertexes_.empty()) {
    object_->vertexes_.clear();
  }
  if (!object_->facets_.empty()) {
    object_->facets_.clear();
  }
}

bool Model::ReadDataFile(std::string &file_name) {
  Clear();
  bool res = true;
  parcer_ = new Parser(new ReadOne);
  if (parcer_->ReadFile(file_name, object_)) {
    parcer_->setStrategy(new ReadTwo);
    parcer_->ReadFile(file_name, object_);
  } else
    res = false;
  return res;
}

unsigned int Model::GetVertexCount() { return object_->count_vertex_; }
unsigned int Model::GetEdgesCount() { return object_->count_edges_; }
unsigned int Model::GetFacetsCount() { return object_->count_facets_ * 2; }
double *Model::GetVertexes() { return object_->vertexes_.data(); }
unsigned int *Model::GetFacets() { return object_->facets_.data(); }

void Model::Normalize() { normalization_.Normalize(*object_); }
} // namespace s21