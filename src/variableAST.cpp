#include "ast/variableAST.h"
#include "sstream"

VariableExprAST::VariableExprAST(const std::string& name) : m_name(name) {}

std::string VariableExprAST::toString() {
    std::stringstream ss;
    ss << "<Variable " << m_name << ">";
    return ss.str();
}

Value VariableExprAST::evaluate() {
    return Value(1.0);
}
