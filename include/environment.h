#pragma once
#include <unordered_map>
#include "value.h"

class Environment {
  std::unordered_map<std::string, Value> mem;
  Environment* m_parent;
public:
  Environment(Environment* parent = nullptr);
  void declareVariable(std::string name, Value v = Value());
  void assignVariable(std::string name, Value v);
  bool hasVariable(const std::string& name) const;
  Value getValue(std::string name);
};
