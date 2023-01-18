#pragma once
#include "ast/ast.h"
#include <memory>

class ExprStmtAST : public StmtAST {
  std::unique_ptr<ExprAST> m_expr;
public:
  ExprStmtAST(std::unique_ptr<ExprAST>& expr);
  virtual void execute(Environment& env) override;
};
