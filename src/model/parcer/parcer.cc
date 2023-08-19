#include "parcer.h"

namespace s21 {

bool ReadOne::Search(std::string file_name, DataModel *data_model) {
  bool res = true;
  std::ifstream fp(file_name);
  if (fp.is_open()) {
    std::string str = "";
    while (std::getline(fp, str)) {
      if (str[0] == 'v' && str[1] == ' ') {
        data_model->count_vertex_ += 3;
      }
      if (str[0] == 'f' && str[1] == ' ') {
        data_model->count_edges_++;
        data_model->count_facets_ += getCountMemory(str);
      }
    }
    fp.close();
  } else {
    res = false;
  }
  if ((!data_model->count_vertex_) || (!data_model->count_edges_)) {
    res = false;
  }
  return res;
};

unsigned int ReadOne::getCountMemory(std::string &str) {
  unsigned int res = 0;
  for (size_t i = 0; i <= str.size(); ++i) {
    if (str[i] >= '0' && str[i] <= '9') {
      if ((str[i - 1] == ' ') || ((str[i - 1] == '-') && (str[i - 2] == ' '))) {
        res++;
      }
    }
  }
  return res;
}

bool ReadTwo::Search(std::string file_name, DataModel *data_model) {
  bool res = true;
  std::ifstream fp(file_name);
  if (fp.is_open()) {
    std::string str = "";
    while (std::getline(fp, str)) {
      if (((str[0] == 'v') || (str[0] == 'f')) && (str[1] == ' ')) {
        getDigit(str, data_model);
      }
    }
    fp.close();
  } else {
    res = false;
  }
  if ((data_model->facets_.empty()) || (data_model->vertexes_.empty())) {
    res = false;
  }

  return res;
}

bool ReadTwo::getDigit(std::string &str, DataModel *data_model) {
  bool res = true; // возможно нужно переделать на void
  std::stringstream ss(str);
  std::string buffer;
  // int step = 0;
  // unsigned int first_element = 0;
  if (str[0] == 'v') {
    while (std::getline(ss, buffer, ' ')) {
      if ((isdigit(buffer[0]) || (isdigit(buffer[1])))) {
        data_model->vertexes_.push_back(stof(buffer));
      }
    }
  }
  if (str[0] == 'f') {
    int step = 0;
    unsigned int first_element = 0;
    while (std::getline(ss, buffer, ' ')) {
      if ((isdigit(buffer[0]) || (isdigit(buffer[1])))) {
        PushToFacets(buffer, first_element, step, data_model);
      }
    }
    if (step) {
      data_model->facets_.push_back(first_element - 1);
    }
  }
  return res;
}

void ReadTwo::PushToFacets(std::string &str, unsigned int &first_element,
                           int &step, DataModel *data_model) {
  double value = 0;
  double x = 0;
  if (step == 0) {
    step = 1;
    x = stof(str);
    if (x < 0) {
      x = data_model->count_facets_ + x;
    }
    first_element = x;
    data_model->facets_.push_back(first_element - 1);
  } else {
    value = stof(str);
    if (value < 0) {
      value = data_model->count_facets_ + value;
    }
    data_model->facets_.push_back(value - 1);
    data_model->facets_.push_back(value - 1);
  }
}

Parser::~Parser() { delete read_; }

void Parser::setStrategy(Read *read) {
  if (read_ != nullptr) {
    delete read_;
  }
  read_ = read;
}

bool Parser::ReadFile(std::string name_file, DataModel *data_model) {
  bool flag = read_->Search(name_file, data_model);
  return flag;
}
} // namespace s21