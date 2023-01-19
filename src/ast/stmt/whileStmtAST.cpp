#include "ast/stmt/whileStmtAST.h"
#include <utility>

WhileStmtAST::WhileStmtAST(std::unique_ptr<StmtAST>& body, std::unique_ptr<ExprAST>& condition)
  : m_body(std::move(body)), m_condition(std::move(condition)) {}

void WhileStmtAST::execute(Environment &env) {
  while(m_condition -> evaluate(env).truth()) 
    m_body -> execute(env);
}
