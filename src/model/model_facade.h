#ifndef MODEL_H_
#define MODEL_H_

#include "normalization/normalization.h"
#include "parcer/parcer.h"

class Model {
public:
  Model() {
    object_ = new DataModel;
    transform_ = new Transform;
  }

  ~Model() {}
  void ChangeModel(std::string action, double value, int axis);
  void Normalize();

  unsigned int GetVertexCount();
  unsigned int GetEdgesCount();
  unsigned int GetFacetsCount();
  void Clear();
  // std::vector<double> GetVertexes();
  // std::vector<unsigned int> GetFacets();
  double *GetVertexes();
  unsigned int *GetFacets();

  bool ReadDataFile(std::string &file_name);

private:
  Normalization normalization_{};
  TransformationContext strategy_{};
  DataModel *object_;
  Transform *transform_;
  Parser *parcer_;
};

#endif // MODEL_H_
