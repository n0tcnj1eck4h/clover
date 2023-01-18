#include "ast/expr/binopExprAST.h"
#include "sstream"

BinaryOpExprAST::BinaryOpExprAST(Operator op, std::unique_ptr<ExprAST>& lhs, std::unique_ptr<ExprAST>& rhs)
    : m_operator(op), m_lhs(std::move(lhs)), m_rhs(std::move(rhs)) {}

std::string BinaryOpExprAST::toString() {
    std::stringstream ss;
    ss << "(" << m_lhs->toString() << ", " << (int)m_operator << ", " << m_rhs->toString() << ")";
    return ss.str();
}

Value BinaryOpExprAST::evaluate() {
    switch(m_operator) {
        case Operator::EQ:
            return Value(m_lhs -> evaluate() == m_rhs -> evaluate() ? 1.0 : 0.0);
        case Operator::NEQ:
            return Value(m_lhs -> evaluate() != m_rhs -> evaluate() ? 1.0 : 0.0);
        case Operator::ADD:
            return Value(m_lhs -> evaluate() + m_rhs -> evaluate());
        case Operator::SUB:
            return Value(m_lhs -> evaluate() - m_rhs -> evaluate());
        case Operator::MUL:
            return Value(m_lhs -> evaluate() * m_rhs -> evaluate());
        case Operator::DIV:
            return Value(m_lhs -> evaluate() / m_rhs -> evaluate());
        case Operator::DIV_FLR:
            return Value(m_lhs -> evaluate().divFloor(m_rhs -> evaluate()));
        case Operator::POW:
            return Value(m_lhs -> evaluate().power(m_rhs -> evaluate()));
        default:
            return Value();
    }
}
