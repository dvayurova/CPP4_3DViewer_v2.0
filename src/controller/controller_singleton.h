#ifndef SRC_CONTROLLER_CONTROLLER_H_
#define SRC_CONTROLLER_CONTROLLER_H_

#include "../model/model_facade.h"

#include <iostream>

// namespace s21 {

class Controller {
public:
  Controller(const Controller &) = delete;
  Controller(Controller &&) = delete;
  Controller &operator=(const Controller &) = delete;
  Controller &operator=(Controller &&) = delete;

  static Controller *Instance();

  void SetModel(Model *model);
  void Normalize();
  void ChangeModel(std::string action, double value, int axis);
  size_t GetVertexCount();
  size_t GetEdgesCount();
  // std::vector<double> GetVertexes();
  // std::vector<unsigned int> GetFacets();
  double *GetVertexes();
  unsigned int *GetFacets();
  unsigned int GetFacetsCount();
  bool ReadDataFile(std::string &file_name);

private:
  Controller() {}
  ~Controller() { delete instance_; }
  static Controller *instance_;
  Model *model_;
};

// } // namespace s21

#endif //  SRC_CONTROLLER_CONTROLLER_H_
