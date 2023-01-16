#pragma once

#include <exception>
#include <token.h>

class UnexpectedTokenException : public std::exception {
    Token m_token;
    std::string m_expected_tokens;
    std::string m_exception;

  public:
    UnexpectedTokenException(Token token, const std::string expectation);
    virtual const char* what() const noexcept override;
    Token getToken() const;
};

class TypeMismatchException : public std::exception {
    public:
        virtual const char* what() const noexcept override;
};
