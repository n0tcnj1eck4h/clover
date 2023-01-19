#include "value.h"
#include "errors.h"
#include <cmath>
#include <math.h>
#include <sstream>

Value::Value(const Value::Variant& data) : m_data(data) {}

//Value::Value(bool boolean) : m_data(boolean ? 1.0 : 0.0) {}

bool Value::operator==(const Value& v) const {
  return v.m_data == m_data;
}

std::string Value::toString() const {
  switch((Value::Type)m_data.index()) {
    case Type::STRING:
    {
      std::string data = std::get<std::string>(m_data);
      return data;
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

  throw TypeMismatchException();
}

Value Value::operator+(const Value& v) const {
  switch(getType()) {
    case Type::STRING:
    {
      std::string l = toString();
      std::string r = v.toString();
      return Value(l + r);
    }

    case Type::NIL:
      throw TypeMismatchException();

    case Type::NUMBER:
    {
      if(v.getType() != Type::NUMBER) return Value(toString()) + v;
      f64 l = std::get<f64>(m_data);
      f64 r = std::get<f64>(v.m_data);
      return Value(l + r);
    }
  }

  throw TypeMismatchException();
}

Value Value::operator-(const Value& v) const {
  switch(getType()) {
    case Type::STRING:
    case Type::NIL:
      throw TypeMismatchException();

    case Type::NUMBER:
    {
      if(v.getType() != Type::NUMBER) throw TypeMismatchException();
      f64 l = std::get<f64>(m_data);
      f64 r = std::get<f64>(v.m_data);
      return Value(l - r);
    }
  }

  throw TypeMismatchException();
}

Value Value::operator*(const Value& v) const {
  switch(getType()) {
    case Type::STRING:
      if(v.getType() == Type::NUMBER) return v * *this;
    case Type::NIL:
      return Value();

    case Type::NUMBER:
    {
      f64 l = std::get<f64>(m_data);

      if(v.getType() == Type::STRING) {
        std::stringstream ss;
        std::string r = std::get<std::string>(v.m_data);
        for(int i = 0; i < l; i++) {
          ss << r;
        }

        return Value(ss.str());
      }

      f64 r = std::get<f64>(v.m_data);
      return Value(l * r);
    }
  }

  throw TypeMismatchException();
}

Value Value::operator/(const Value& v) const {
  if(getType() == Type::NUMBER && v.getType() == Type::NUMBER) {
    f64 l = std::get<f64>(m_data);
    f64 r = std::get<f64>(v.m_data);
    return Value(l / r);
  }

  throw TypeMismatchException();
}

bool Value::operator<(const Value& v) const {
  if(getType() == Type::NUMBER && v.getType() == Type::NUMBER) {
    f64 l = std::get<f64>(m_data);
    f64 r = std::get<f64>(v.m_data);
    return l < r;
  }

  throw TypeMismatchException();
}

bool Value::operator>(const Value& v) const {
  if(getType() == Type::NUMBER && v.getType() == Type::NUMBER) {
    f64 l = std::get<f64>(m_data);
    f64 r = std::get<f64>(v.m_data);
    return l > r;
  }

  throw TypeMismatchException();
}

bool Value::operator>=(const Value& v) const {
  return *this > v || *this == v;
}

bool Value::operator<=(const Value& v) const {
  return *this < v || *this == v;
}

bool Value::operator&&(const Value& v) const {
  return truth() && v.truth();
}

bool Value::operator||(const Value& v) const {
  return truth() || v.truth();
}

Value Value::power(const Value &v) const {
  if(getType() == Type::NUMBER && v.getType() == Type::NUMBER) {
    f64 l = std::get<f64>(m_data);
    f64 r = std::get<f64>(v.m_data);
    return Value(pow(l, r));
  }

  throw TypeMismatchException();
}

Value Value::divFloor(const Value &v) const {
  if(getType() == Type::NUMBER && v.getType() == Type::NUMBER) {
    f64 l = std::get<f64>(m_data);
    f64 r = std::get<f64>(v.m_data);
    return Value((f64)((int)l / (int)r));
  }

  throw TypeMismatchException();
}

bool Value::truth() const {
  switch(getType()) {
    case Type::STRING:
    {
      std::string r = std::get<std::string>(m_data);
      return r.length() != 0;
    }

    case Type::NIL:
      return false;

    case Type::NUMBER:
    {
      f64 r = std::get<f64>(m_data);
      return r != 0.0;
    }
  }

  return false;
}
