#pragma once
#include "ast/AST.h"
#include <memory>

class PrintStmtAST : public StmtAST {
  std::unique_ptr<ExprAST> m_expr;
public:
  PrintStmtAST(std::unique_ptr<ExprAST>& expr);
  virtual void evaluate() override;
	virtual std::string toString() override;
};
