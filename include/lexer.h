#pragma once
#include <istream>
#include "token.h"

class Lexer {
	private:
		std::istream& stream;
		char get();
		char peek();
		bool match(char c);
		// TODO
		u32 row, column;

	public:
		Lexer(std::istream& stream);
		Token getToken();
		Token getToken2();
};
