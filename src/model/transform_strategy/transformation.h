#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include <algorithm>
#include <cmath>
#include <vector>

#include "../data/data_model.h"

class TransformationStrategy {
public:
  virtual ~TransformationStrategy() {}
  virtual void TransformModel(DataModel &model, Transform &transform) = 0;
};

class Rotation : public TransformationStrategy {
public:
  ~Rotation() {}
  void TransformModel(DataModel &model, Transform &transform) override;

private:
  static constexpr double kConvertAngle = M_PI / 180;
  double GetAngle(Transform &transform);
  void SavePrevAngle(Transform &transform);
};

class Scaling : public TransformationStrategy {
public:
  ~Scaling() {}
  void TransformModel(DataModel &model, Transform &transform) override;
};

class Translation : public TransformationStrategy {
public:
  void TransformModel(DataModel &model, Transform &transform) override;
};

class TransformationContext {
public:
  ~TransformationContext() {}
  void SetStrategy(TransformationStrategy *strategy) { strategy_ = strategy; }
  void ExecuteTransformStrategy(DataModel &model, Transform &transform) {
    strategy_->TransformModel(model, transform);
  }

private:
  TransformationStrategy *strategy_;
};

#endif // TRANSFORMATION_H