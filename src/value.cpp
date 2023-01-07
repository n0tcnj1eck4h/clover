#include "value.h"
#include <sstream>

Value::Value(const Value::Variant& data) : m_data(data) {}
bool Value::operator==(const Value& v) const {
  return v.m_data == m_data;
}

std::string Value::toString() const {
  switch((Value::Type)m_data.index()) {
    case Type::STRING:
    {
      std::string data = std::get<std::string>(m_data);
      return '"' + data + '"';
    }
    case Type::NIL:
      return "NIL";
    case Type::NUMBER:
    {
      f64 data = std::get<f64>(m_data);
      std::stringstream ss;
      ss << data;
      return ss.str();
    }
  }

  return "Error";
}
