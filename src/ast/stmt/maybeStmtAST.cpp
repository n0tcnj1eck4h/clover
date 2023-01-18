#include "ast/stmt/maybeStmtAST.h"
#include <cstdlib>

MaybeStmtAST::MaybeStmtAST(std::unique_ptr<StmtAST>& statement) 
  : m_statement(std::move(statement)) {}

void MaybeStmtAST::execute(Environment &env) {
  if(rand() % 2) {
    m_statement->execute(env);
  }
}
