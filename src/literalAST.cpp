#include "ast/literalAST.h"
#include "sstream"

LiteralAST::LiteralAST(const Value& value) : m_value(value) {}

std::string LiteralAST::toString() {
    return m_value.toString();
}

Value LiteralAST::evaluate() {
    return m_value;
}
