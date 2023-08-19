#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include <algorithm>
#include <cmath>
#include <vector>

#include "../data/data_model.h"

namespace s21 {

class Transformation {
public:
  Transformation() {}
  ~Transformation() {}
  void Rotate(DataModel &model, Transform &transform);
  void Scale(DataModel &model, Transform &transform);
  void Translate(DataModel &model, Transform &transform);

private:
  static constexpr double kConvertAngle = M_PI / 180;
  double GetAngle(Transform &transform);
  void SavePrevAngle(Transform &transform);
};
} // namespace s21

#endif // TRANSFORMATION_H