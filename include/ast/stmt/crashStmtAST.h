#pragma once
#include "ast/ast.h"

class CrashStmtAST : public StmtAST {
public:
  virtual void execute(Environment& env) override;
};
