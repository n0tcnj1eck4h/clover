#pragma once
#include "ast/ast.h"
#include "environment.h"
#include <memory>
#include <vector>

class BlockStmtAST : public StmtAST {
  std::vector<std::unique_ptr<StmtAST>> m_statements;
public:
  BlockStmtAST(std::vector<std::unique_ptr<StmtAST>>& statements);
	virtual void execute(Environment& env) override;
};
