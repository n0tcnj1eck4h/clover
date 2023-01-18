#include <cctype>
#include <exception>
#include <iostream>
#include <istream>
#include <limits>
#include <string>
#include "errors.h"
#include "lexer.h"
#include "token.h"

Lexer::Lexer(std::istream& stream) : stream(stream), row(0), column(0) {};

char Lexer::get() {
    if(peek() == '\n') {
        column = 0;
        row++;
    }
    else column++;
    return stream.get();
}

char Lexer::peek() {
    return stream.peek();
}

bool Lexer::match(char c) {
    if(peek() != c) return false;
    return get();
}

Token Lexer::getToken() {
    auto token = getToken2();
    token.col = column;
    token.row = row;
    return token;
}

Token Lexer::getToken2() {
    // Skip whitespace
    while(std::isspace(peek())) get();

    // Check for end of file
    if(stream.peek() == std::char_traits<char>::eof()) return Token();

    // Skip comments
    if(match('#')) {
        stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        column++;
        return getToken();
    }

    // Operators
    if(match('!')) return Token(match('=') ? Operator::NEQ     : Operator::BANG  );
    if(match('=')) return Token(match('=') ? Operator::EQ      : Operator::ASSIGN);
    if(match('>')) return Token(match('=') ? Operator::GTQ     : Operator::GTR   );
    if(match('<')) return Token(match('=') ? Operator::LTQ     : Operator::LESS  );
    if(match('*')) return Token(match('*') ? Operator::POW     : Operator::MUL   );
    if(match('/')) return Token(match('/') ? Operator::DIV_FLR : Operator::DIV   );
    if(match('+')) return Token(Operator::ADD);
    if(match('-')) return Token(Operator::SUB);
    if(match('|')) return Token(Operator::OR);
    if(match('&')) return Token(Operator::AND);
    if(match(',')) return Token(Atom::COMMA);
    if(match('(')) return Token(Atom::PAREN_OPEN);
    if(match(')')) return Token(Atom::PAREN_CLOSE);
    if(match(';')) return Token(Atom::END_STATEMENT);

    // Identifiers start with a letter or '_'
    if(std::isalpha(peek()) || peek() == '_') {
        std::string temp;
        while(std::isalnum(peek()) || peek() == '_') {
            temp += get();
        }

        if(temp == "var")    return Token(Keyword::VAR);
        // if(temp == "def")    return Token(Keyword::DEFINE);
        // if(temp == "extern") return Token(Keyword::EXTERN);
        if(temp == "print")  return Token(Keyword::PRINT);

        return Token(Token::Identifier(temp));
    }

    // String literals start with a '"'
    if(match('"')) {
        std::string temp;
        while(!match('"')) {
            temp += get();
        }

        return Token(Token::Literal(temp));
    }

    // Numeric literals start with a number
    if(std::isdigit(peek())) {
        i64 integer = 0;
        f64 decimal = 0.0;
        f64 div = 10.0;

        while(std::isdigit(peek())) {
            integer = integer * 10 + get() - '0';
        }

        if(match('.')) {
            while(std::isdigit(peek())) {
                decimal = decimal + (f64)(get() - '0') / div;
                div *= 10.0;
            }
        }

        return Token(Token::Literal((f64)integer + decimal));
    }

    std::string temp;
    stream >> temp;
	throw UnexpectedStringException(temp);
}
