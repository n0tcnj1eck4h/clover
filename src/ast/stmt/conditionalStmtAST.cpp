#include "ast/stmt/conditionalStmtAST.h"
#include <utility>

ConditionalStmtAST::ConditionalStmtAST(
    std::unique_ptr<ExprAST>& condition,
    std::unique_ptr<StmtAST>& then_branch,
    std::unique_ptr<StmtAST>& else_branch)
: m_condition(std::move(condition)), 
  m_then_branch(std::move(then_branch)),
  m_else_branch(std::move(else_branch)) { }

ConditionalStmtAST::ConditionalStmtAST(
    std::unique_ptr<ExprAST>& condition,
    std::unique_ptr<StmtAST>& then_branch)
: m_condition(std::move(condition)), 
  m_then_branch(std::move(then_branch)),
  m_else_branch(nullptr) { }

void ConditionalStmtAST::execute(Environment &env) {
    if(m_condition->evaluate(env).truth()) 
        m_then_branch->execute(env);
    else if(m_else_branch != nullptr)
        m_else_branch->execute(env);
}
