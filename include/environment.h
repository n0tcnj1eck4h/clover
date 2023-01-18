#pragma once
#include <unordered_map>
#include "value.h"

class Environment {
  std::unordered_map<std::string, Value> mem;
public:
  void declareVariable(std::string name, Value v = Value());
  void assignVariable(std::string name, Value v);
  Value getValue(std::string name);
};
