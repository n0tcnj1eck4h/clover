#pragma once
#include <string>
#include <variant>
#include "enums.h"
#include "types.h"
#include "value.h"

class Token {
public:
  enum class Type {
    EndOfFile,
    Identifier,
    Keyword,
    Operator,
    Atom,
    Literal,
  };

  using Identifier = std::string;
  using Literal = Value;
  using Variant = std::variant<std::monostate, Identifier, Keyword, Operator, Atom, Literal>;

  Token(const Variant& data = std::monostate());
  std::string toString() const;
  Type getType() const;

  template<typename T>
  T get();

  template<typename T>
  bool get(T& val);

  bool operator==(const Token& t) const;

  
  //bool matchKeyword(Keyword keyword);
  // bool getValue(f64 &decimal, bool should_throw = true);
  // bool getValue(i64 &integer, bool should_throw = true);
  // bool getValue(Identifier &identifier, bool should_throw = true);


private:
  Variant m_data;
};

template<typename T>
T Token::get() {
  return std::get<T>(m_data);
}

template<typename T>
bool Token::get(T& val) {
  auto v = std::get_if<T>(m_data);
  if(!v)
    return false;

  val = *v;
  return true;
}

/*
struct Token {
        enum class KeywordEnum : u32 {
                DEFINE,
                EXTERN,
        };

        enum class AtomEnum : u8 {
                PARENTHESIS_OPEN =  '(',
                PARENTHESIS_CLOSE = ')',
                COMMA = ','
        };

        struct EndOfFile { };
        struct Unexpected { std::string token; };
        struct Number { f64 value; };
        struct Identifier { std::string name; };
        struct Atom { AtomEnum atom; };
        struct Keyword { KeywordEnum keyword; };
};

using TokenVariant = std::variant<
        Token::EndOfFile,
        Token::Unexpected,
        Token::Number,
        Token::Keyword,
        Token::Identifier,
        Token::Atom
>; */
