#include <iostream>
#include <fstream>
#include <variant>
#include "lexer.h"
#include "token.h"

template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

int main(int argc, const char** argv) {
   Lexer lexer(std::cin);

    while(true) {
        TokenVariant token = lexer.getToken();
	std::visit(overloaded { 
		[](Token::EndOfFile& )   { std::cout << "End of file." << std::endl; },
		[](Token::Unexpected& u) { std::cout << "Unexpected identifier: " << u.token << std::endl; },
		[](Token::Number& n)     { std::cout << "Number: " << n.value << std::endl; },
		[](Token::Keyword& k)    { std::cout << "Keyword: " << (u32)k.keyword << std::endl; },
		[](Token::Identifier& i) { std::cout << "Identifier: " << i.name << std::endl; },
		[&](auto& )              { std::cout << "Unhandled Token ID: " << token.index() << std::endl; }
	}, token);

	if(std::get_if<Token::EndOfFile>(&token)) break;
    }

	return 0;
}
