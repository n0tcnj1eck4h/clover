#pragma once
#include "types.h"
#include <string>
#include <variant>

class Token {
public:
  enum class Type {
    EndOfFile,
    Integer,
    Decimal,
    Identifier,
    Keyword,
    Atom,
  };

  enum class Keyword : u8 { Define, Extern };
  struct Identifier { std::string identifier; };
  struct Atom { char atom; };

  Token() = delete;
  Token(Type type);
  Token(Atom atom);
  Token(f64 decimal);
  Token(i64 integer);
  Token(Keyword keyword);
  Token(const Identifier &identifier);

  Type getType() const;
  bool matchAtom(char atom);
  bool matchKeyword(Keyword keyword);

  bool getValue(f64 &decimal, bool should_throw = true);
  bool getValue(i64 &integer, bool should_throw = true);
  bool getValue(Atom &atom, bool should_throw = true);
  bool getValue(Identifier &identifier, bool should_throw = true);

  std::string toString() const;

private:
  Type m_type;
  std::variant<Atom, f64, i64, Identifier, Keyword> m_data;
};

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
