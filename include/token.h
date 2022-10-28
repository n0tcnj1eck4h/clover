#pragma once
#include <variant>
#include <string>
#include "types.h"

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
>;
