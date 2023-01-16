#include "ast/literalAST.h"
#include "sstream"

LiteralAST::LiteralAST(const Value& value) : m_value(value) {}

std::string LiteralAST::toString() {
    std::stringstream ss;
    ss << "<Value " << m_value.toString() << ">";
    return ss.str();
}

Value LiteralAST::evaluate() {
    return m_value;
}
