#pragma once

#include <exception>
#include <token.h>

// Parser error
class UnexpectedTokenException : public std::exception {
    Token m_token;
    std::string m_expected_tokens;
    std::string m_exception;

  public:
    UnexpectedTokenException(Token token, const std::string expectation);
    virtual const char* what() const noexcept override;
    Token getToken() const;
};

// Lexer error
class UnexpectedStringException : public std::exception {
    std::string m_string;
    std::string m_exception;

public:
    UnexpectedStringException(std::string& string);
    virtual const char* what() const noexcept override;
};

// Runtime error
class TypeMismatchException : public std::exception {
    public:
        virtual const char* what() const noexcept override;
};
