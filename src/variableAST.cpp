#include "ast/variableAST.h"
#include "sstream"

VariableExprAST::VariableExprAST(const std::string& name) : m_name(name) {}

std::string VariableExprAST::toString() {
    return "$" + m_name;
}

Value VariableExprAST::evaluate() {
    return Value(1.0);
}
