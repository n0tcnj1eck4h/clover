#include "token.h"
#include <errors.h>
#include <sstream>

UnexpectedTokenException::UnexpectedTokenException(Token token, const std::string expectation) 
  : m_token(token), m_expectation(expectation) {}

const char* UnexpectedTokenException::what() const noexcept {
  static std::string ret;
  std::stringstream ss;
  ss << "Unexpected token " << m_token.toString() << ". " << m_expectation << " expected\n";
  ret = ss.str();
 return ret.c_str();
}
