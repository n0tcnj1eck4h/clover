#include "ast/stmt/vardeclStmtAST.h"
#include <unordered_map>
#include "value.h"

VardeclStmtAST::VardeclStmtAST(std::string identifier, std::unique_ptr<ExprAST>& initilizer) 
  : m_identifier(identifier), m_initilizer(std::move(initilizer)) { }


void VardeclStmtAST::execute(Environment& env) {
  env.declareVariable(m_identifier, m_initilizer -> evaluate(env));
}

