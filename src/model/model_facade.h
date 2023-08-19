#ifndef MODEL_H_
#define MODEL_H_

#include "normalization/normalization.h"
#include "parcer/parcer.h"

namespace s21 {

class Model {
public:
  Model() {
    object_ = new DataModel;
    transform_ = new Transform;
  }

  ~Model() {
    delete object_;
    delete transform_;
    delete parcer_;
  }
  void ChangeModel(std::string action, double value, int axis);
  void Normalize();

  unsigned int GetVertexCount();
  unsigned int GetEdgesCount();
  unsigned int GetFacetsCount();
  void Clear();
  double *GetVertexes();
  unsigned int *GetFacets();

  bool ReadDataFile(std::string &file_name);

private:
  Normalization normalization_{};
  Transformation transformation_;
  DataModel *object_;
  Transform *transform_;
  Parser *parcer_;
};
} // namespace s21

#endif // MODEL_H_
