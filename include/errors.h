#pragma once

#include <exception>
#include <token.h>

class UnexpectedTokenException : public std::exception {
    Token m_token;
    std::string m_expectation;

  public:
    UnexpectedTokenException(Token token, const std::string expectation);
    virtual const char* what() const noexcept override;
};
