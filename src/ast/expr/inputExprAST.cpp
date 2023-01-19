#include "ast/expr/inputExprAST.h"
#include <iostream>
#include <string>

Value InputExprAST::evaluate(Environment &env) {
  std::cout << std::endl << "< ";
  std::string temp;
  std::getline(std::cin, temp);
  return Value(temp);
}
