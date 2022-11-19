#pragma once
#include "types.h"
#include <string>
#include <sys/types.h>
#include <variant>

class Token {
public:
  enum class Type {
    EndOfFile,
    Integer,
    Float,
    Identifier,
    Keyword,
    Atom,
    What
  };

  enum class Keyword { Define, Extern };

  Token() = delete;
  Token(Type type);
  Token(char atom);
  Token(f64 decimal);
  Token(i64 integer);
  Token(Keyword keyword);
  Token(const std::string &identifier);

  Type getType() const;
  bool matchAtom(char atom);
  bool matchKeyword(Keyword keyword);

  bool getValue(f64 &decimal);
  bool getValue(i64 &integer);
  bool getValue(char &atom);
  bool getValue(std::string &identifier);

private:
  Type m_type;
  std::variant<char, f64, i64, std::string, Keyword> m_data;
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
