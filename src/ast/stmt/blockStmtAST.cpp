#include "ast/stmt/blockStmtAST.h"
#include "environment.h"

BlockStmtAST::BlockStmtAST(std::vector<std::unique_ptr<StmtAST>>& statements) 
  : m_statements(std::move(statements)) {}

void BlockStmtAST::execute(Environment &env) {
  Environment local_env(&env);
  for(auto& s : m_statements) {
    s->execute(local_env);
  }
}
