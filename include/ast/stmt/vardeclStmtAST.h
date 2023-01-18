#pragma once
#include "ast/ast.h"
#include <memory>

class VardeclStmtAST : public StmtAST {
  std::string m_identifier;
  std::unique_ptr<ExprAST> m_initilizer;
public:
  VardeclStmtAST(std::string identifier, std::unique_ptr<ExprAST>& initilizer);
  virtual void execute(Environment& env) override;
};
