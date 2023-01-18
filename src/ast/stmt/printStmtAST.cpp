#include "ast/stmt/printStmtAST.h"
#include <memory>
#include <iostream>
#include <sstream>

PrintStmtAST::PrintStmtAST(std::unique_ptr<ExprAST>& expr) : m_expr(std::move(expr)) {}

void PrintStmtAST::execute() {
  std::cout << m_expr -> evaluate() . toString() << std::endl;
}

std::string PrintStmtAST::toString() {
  std::stringstream ss;
  ss << "print" << m_expr->toString() << ";";
  return ss.str();
}
