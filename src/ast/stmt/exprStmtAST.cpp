#include "ast/stmt/exprStmtAST.h"

ExprStmtAST::ExprStmtAST(std::unique_ptr<ExprAST>& expr) 
  : m_expr(std::move(expr)) {}

void ExprStmtAST::execute(Environment& env) {
  m_expr -> evaluate(env);
}
