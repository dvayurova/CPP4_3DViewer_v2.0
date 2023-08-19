#ifndef DATA_MODEL_H_
#define DATA_MODEL_H_

#include <array>
#include <vector>

enum Axis { kX, kY, kZ };

struct DataModel {
  unsigned int count_vertex_;
  unsigned int count_facets_;
  unsigned int count_edges_;
  std::vector<double> vertexes_;
  std::vector<unsigned int> facets_;
};

struct Transform {
  double value;
  int axis;
  double prev_angle_x;
  double prev_angle_y;
  double prev_angle_z;

  std::array<double, 3> prev_coor_;
};

#endif // DATA_MODEL_H_