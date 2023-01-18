#include "ast/expr/variableExprAST.h"
#include "sstream"

VariableExprAST::VariableExprAST(const std::string& name) : m_name(name) {}

std::string VariableExprAST::toString() {
    return "$" + m_name;
}

Value VariableExprAST::evaluate(Environment& env) {
    return env.getValue(m_name);
}
