#pragma once
#include "ast/ast.h"
#include "environment.h"
#include <memory>

class PrintStmtAST : public StmtAST {
  std::unique_ptr<ExprAST> m_expr;
public:
  PrintStmtAST(std::unique_ptr<ExprAST>& expr);
  virtual void execute(Environment& env) override;
	virtual std::string toString() override;
};
