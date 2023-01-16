#include "value.h"
#include <cmath>
#include <math.h>
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

Value Value::operator+(const Value& v) const {
  if(v.getType() != getType()) {
    return Value("Type error");
  }
  
  switch(getType()) {
    case Type::STRING:
    {
      std::string l = std::get<std::string>(m_data);
      std::string r = std::get<std::string>(v.m_data);
      return Value(l + r);
    }
    case Type::NIL:
      return Value();

    case Type::NUMBER:
    {
      f64 l = std::get<f64>(m_data);
      f64 r = std::get<f64>(v.m_data);
      return Value(l + r);
    }
  }

  return Value();
}

Value Value::operator-(const Value& v) const {
  if(v.getType() != getType()) {
    return Value("Type error");
  }
  
  switch(getType()) {
    case Type::STRING:
    case Type::NIL:
      return Value();

    case Type::NUMBER:
    {
      f64 l = std::get<f64>(m_data);
      f64 r = std::get<f64>(v.m_data);
      return Value(l - r);
    }
  }

  return Value();
}

Value Value::operator*(const Value& v) const {
  if(v.getType() != getType()) {
    return Value("Type error");
  }
  
  switch(getType()) {
    case Type::STRING:
    case Type::NIL:
      return Value();

    case Type::NUMBER:
    {
      f64 l = std::get<f64>(m_data);
      f64 r = std::get<f64>(v.m_data);
      return Value(l * r);
    }
  }

  return Value();
}

Value Value::operator/(const Value& v) const {
  if(v.getType() != getType()) {
    return Value("Type error");
  }
  
  switch(getType()) {
    case Type::STRING:
    case Type::NIL:
      return Value();

    case Type::NUMBER:
    {
      f64 l = std::get<f64>(m_data);
      f64 r = std::get<f64>(v.m_data);
      return Value(l / r);
    }
  }

  return Value();
}

Value Value::power(const Value &v) const {
  if(v.getType() != getType()) {
    return Value("Type error");
  }
  
  switch(getType()) {
    case Type::STRING:
    case Type::NIL:
      return Value();

    case Type::NUMBER:
    {
      f64 l = std::get<f64>(m_data);
      f64 r = std::get<f64>(v.m_data);
      return Value(pow(l, r));
    }
  }

  return Value();
}

Value Value::divFloor(const Value &v) const {
  if(v.getType() != getType()) {
    return Value("Type error");
  }
  
  switch(getType()) {
    case Type::STRING:
    case Type::NIL:
      return Value();

    case Type::NUMBER:
    {
      f64 l = std::get<f64>(m_data);
      f64 r = std::get<f64>(v.m_data);
      return Value((f64)((int)l / (int)r));
    }
  }

  return Value();
}
