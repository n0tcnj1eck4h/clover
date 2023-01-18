#include "environment.h"

void Environment::assignVariable(std::string name, Value v) {
  mem.at(name) = v;
}

void Environment::declareVariable(std::string name, Value v) {
  mem.insert_or_assign(name, v);
}

Value Environment::getValue(std::string name) {
  return mem.at(name);
}
