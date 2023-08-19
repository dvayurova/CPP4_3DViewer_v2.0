#ifndef PARCER_H_
#define PARCER_H_

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "../data/data_model.h"

class Read {
 public:
  virtual ~Read(){};
  virtual bool Search(std::string name_file, DataModel* data_model) = 0;
};

class ReadOne : public Read {
 public:
  bool Search(std::string name_file, DataModel* data_model) override;
  unsigned int getCountMemory(std::string& str);
};

class ReadTwo : public Read {
 public:
  bool Search(std::string name_file, DataModel* data_model) override;
  bool getDigit(std::string& str, DataModel* data_model);
  void PushToFacets(std::string& str, unsigned int& first_element, int& step,
                    DataModel* data_model);
};

class Parser {
 public:
  Parser(Read* read) : read_(read){};
  ~Parser();
  void setStrategy(Read* read);
  bool ReadFile(std::string name_file, DataModel* data_model);

 private:
  Read* read_;
};
#endif  // PARCER_H_
