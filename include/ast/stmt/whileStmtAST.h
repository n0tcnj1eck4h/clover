#pragma once
#include "ast/ast.h"
#include <memory>

class WhileStmtAST : public StmtAST {
  std::unique_ptr<StmtAST> m_body;
  std::unique_ptr<ExprAST> m_condition;
public:
  WhileStmtAST(std::unique_ptr<StmtAST>& body, std::unique_ptr<ExprAST>& condition);
  virtual void execute(Environment& env) override;
};
