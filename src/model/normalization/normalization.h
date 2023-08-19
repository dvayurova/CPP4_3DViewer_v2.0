#ifndef NORMALIZATION_H_
#define NORMALIZATION_H_

#include "../transform_strategy/transformation.h"

namespace s21 {
class Normalization {
public:
  Normalization() {}
  ~Normalization() {}
  void Normalize(DataModel &model);

private:
  void Centering(DataModel &model);
  double GetCenter(std::vector<double> coordinates);
  std::vector<double> GetCoordinates(DataModel &model, int axis);
  static constexpr double kDefaultScale = 0.3;
};

} // namespace s21

#endif // NORMALIZATION_H_