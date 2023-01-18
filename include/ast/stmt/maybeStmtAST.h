#pragma once
#include "ast/ast.h"
#include <memory>

class MaybeStmtAST : public StmtAST {
  std::unique_ptr<StmtAST> m_statement;
public:
  MaybeStmtAST(std::unique_ptr<StmtAST>& statement);
  virtual void execute(Environment& env) override;
};
