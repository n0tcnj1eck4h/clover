#pragma once
#include <istream>
#include <sstream>
#include "token.h"

class Lexer {
	private:
		std::istream& stream;
		
	public:
		Lexer(std::istream& stream);
		const Token getToken();
};
