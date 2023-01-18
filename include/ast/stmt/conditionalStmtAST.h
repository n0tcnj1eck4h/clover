#pragma once
#include "ast/ast.h"
#include <memory>

class ConditionalStmtAST : public StmtAST {
  std::unique_ptr<ExprAST> m_condition;
  std::unique_ptr<StmtAST> m_then_branch;
  std::unique_ptr<StmtAST> m_else_branch;
public:
  ConditionalStmtAST(
      std::unique_ptr<ExprAST>& m_condition,
      std::unique_ptr<StmtAST>& m_then_branch,
      std::unique_ptr<StmtAST>& m_else_branch);

  ConditionalStmtAST(
      std::unique_ptr<ExprAST>& m_condition,
      std::unique_ptr<StmtAST>& m_then_branch);

	virtual void execute(Environment& env) override;
};
