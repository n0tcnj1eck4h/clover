#include "environment.h"

Environment::Environment(Environment* env) : m_parent(env) { 

}

bool Environment::hasVariable(const std::string& name) const {
 return mem.contains(name) || (m_parent && m_parent -> hasVariable(name));
}

void Environment::assignVariable(std::string name, Value v) {
  mem.at(name) = v;
}

void Environment::declareVariable(std::string name, Value v) {
  mem.insert_or_assign(name, v);
}

Value Environment::getValue(std::string name) {
  if(mem.contains(name)) 
    return mem.at(name);
  else if(m_parent)
    return m_parent -> getValue(name);

  return Value();
}
