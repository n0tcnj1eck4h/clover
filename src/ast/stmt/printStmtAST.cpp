#include "ast/stmt/printStmtAST.h"
#include "environment.h"
#include <memory>
#include <iostream>
#include <sstream>

PrintStmtAST::PrintStmtAST(std::unique_ptr<ExprAST>& expr) : m_expr(std::move(expr)) {}

void PrintStmtAST::execute(Environment& env) {
  std::cout << m_expr->evaluate(env).toString() << std::endl;
}

std::string PrintStmtAST::toString() {
  std::stringstream ss;
  ss << "print" << m_expr->toString() << ";";
  return ss.str();
}
