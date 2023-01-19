#include "environment.h"

Environment::Environment(Environment* env) : m_parent(env) { 

}

bool Environment::hasVariable(const std::string& name) const {
 return mem.contains(name) || (m_parent && m_parent -> hasVariable(name));
}

// void Environment::assignVariable(std::string name, Value v) {
//   mem.at(name) = v;
// }

bool Environment::declareVariable(std::string name, Value v) {
  if(m_parent) {
    if(m_parent->hasVariable(name))
      m_parent->declareVariable(name, v);
    else
      mem.insert_or_assign(name, v);
    return true;
  }

  mem.insert_or_assign(name, v);
  return true;
}

Value Environment::getValue(std::string name) {
  if(mem.contains(name)) 
    return mem.at(name);
  else if(m_parent)
    return m_parent -> getValue(name);

  return Value();
}
