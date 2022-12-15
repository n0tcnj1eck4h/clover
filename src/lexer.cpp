#include <cctype>
#include <exception>
#include <ios>
#include <iostream>
#include <istream>
#include <limits>
#include <string>
#include "lexer.h"
#include "token.h"

Lexer::Lexer(std::istream& stream) : stream(stream) {};

Token Lexer::getToken() {
    // Skip whitespace
    while(std::isspace(stream.peek())) stream.get();

    // Check for end of file
    if(stream.peek() == std::char_traits<char>::eof()) return Token::EndOfFile();

    // Skip comments
    if(stream.peek() == '#') {
        stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return getToken();
    }

    // Atoms
    switch(stream.peek()) {
        case '(':
        case ')':
        case '+':
        case '-':
        case '*':
        case '/':
            return Token(Token::Atom{(char)stream.get()});
    }

    // Identifiers start with a letter or '_'
    if(std::isalpha(stream.peek()) || stream.peek() == '_') {
        std::string temp;
        while(std::isalnum(stream.peek()) || stream.peek() == '_') {
            temp += stream.get();
        }

        if(temp == "def")    return Token(Token::Keyword::Define);
        if(temp == "extern") return Token(Token::Keyword::Extern);

        return Token(Token::Identifier{temp});
    }

    // Numeric literals start with a number
    if(std::isdigit(stream.peek())) {
        i64 integer = 0;
        f64 decimal = 0.0;
        f64 div = 10.0;

        while(std::isdigit(stream.peek())) {
            integer = integer * 10 + stream.get() - '0';
        }

        if(stream.peek() == '.') {
            stream.get();
            while(std::isdigit(stream.peek())) {
                decimal = decimal + (f64)(stream.get() - '0') / div;
                div *= 10.0;
            }
        }
        else return Token(integer);

        return Token((f64)integer + decimal);
    }

    std::string temp;
    stream >> temp;
    std::cout << "Unexpected string reached: " << temp << std::endl; 

	throw std::exception();
}
