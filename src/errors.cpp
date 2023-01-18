#include "token.h"
#include <errors.h>
#include <sstream>
#include "ANSI-color-codes.h"

UnexpectedTokenException::UnexpectedTokenException(Token token, const std::string expectation) 
  : m_token(token), m_expected_tokens(expectation) {
    std::stringstream ss;
    ss << RED << "Unexpected " << m_token.toString()
      << " on line " << m_token.row 
      << " column " << m_token.col << ". " 
      << m_expected_tokens << " expected\n"
      << CRESET;
    m_exception = ss.str();
  }

const char* UnexpectedTokenException::what() const noexcept {
  return m_exception.c_str();
}

Token UnexpectedTokenException::getToken() const {
  return m_token;
}

UnexpectedStringException::UnexpectedStringException(std::string& string) : m_string(string) {
  m_exception = (RED "Unexpected string of characters: ") + m_string + "\n" + CRESET;
}

const char* UnexpectedStringException::what() const noexcept {
  return m_exception.c_str();
}

const char* TypeMismatchException::what() const noexcept {
  return "Type mismatch error";
}
