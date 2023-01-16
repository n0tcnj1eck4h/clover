#pragma once

#include <variant>
#include <string>
#include "types.h"

class Value {
  public:
    using Variant = std::variant<std::monostate, f64, std::string>;

    enum class Type {
      NIL,
      NUMBER,
      STRING
    };

    Value(const Variant& data = std::monostate());
    inline Type getType() const { return (Type)m_data.index(); }
    bool operator==(const Value& v) const;
    Value operator+(const Value& v) const;
    Value operator-(const Value& v) const;
    Value operator*(const Value& v) const;
    Value operator/(const Value& v) const;
    Value divFloor(const Value& v) const;
    Value power(const Value& v) const;
    std::string toString() const;

  private:
    Variant m_data;
};
