#include <cctype>
#include <ios>
#include <iostream>
#include <istream>
#include <limits>
#include <string>
#include "lexer.h"
#include "token.h"

Lexer::Lexer(std::istream& stream) : stream(stream) {};

//TokenVariant Lexer::get_token() {
//	if(stream.eof())
//		return Token::EndOfFile{};
//	
//	//stream >> std::skipws >> buffer;
//
//	//if(buffer[0] == '#') {
//	//	stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//	//	return get_token();
//	//}
//
//	if(stream >> float_buffer)
//		return Token::Number{ float_buffer }; else stream.clear();
//
//	stream >> buffer;
//
//	if(buffer == "def")    return Token::Keyword{ Token::KeywordEnum::DEFINE };
//	if(buffer == "extern") return Token::Keyword{ Token::KeywordEnum::EXTERN };
//
//	return Token::Identifier{ buffer };
//}


const TokenVariant Lexer::getToken() {
    // Skip whitespace
    while(std::isspace(stream.peek())) stream.get();

    if(stream.peek() == std::char_traits<char>::eof()) return Token::EndOfFile{ };

    // Skip comments
    if(stream.peek() == '#') {
        stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return getToken();
    }

    // Atoms
    switch(stream.peek()) {
        case '(':
        case ')':
            return Token::Atom { (Token::AtomEnum)stream.get() };
    }

    // Identifiers start with a letter or '_'
    if(std::isalpha(stream.peek()) || stream.peek() == '_') {
        std::string temp;
        while(std::isalnum(stream.peek()) || stream.peek() == '_') {
            temp += stream.get();
        }

        if(temp == "def")    return Token::Keyword { Token::KeywordEnum::DEFINE };
        if(temp == "extern") return Token::Keyword { Token::KeywordEnum::EXTERN };

        return Token::Identifier{ std::move(temp) };
    }

    // Numeric literals start with a number
    if(std::isdigit(stream.peek())) {
        f64 value;
        if(stream >> value) return Token::Number{ value };
        else {
            stream.clear();
            std::string temp;
            stream >> temp;
            return Token::Unexpected{ std::move(temp) };
        }
    }

    std::string temp;
    stream >> temp;
    return Token::Unexpected{ std::move(temp) };
}
