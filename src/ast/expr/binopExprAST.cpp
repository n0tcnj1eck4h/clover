#include "ast/expr/binopExprAST.h"
#include "sstream"

BinaryOpExprAST::BinaryOpExprAST(Operator op, std::unique_ptr<ExprAST>& lhs, std::unique_ptr<ExprAST>& rhs)
    : m_operator(op), m_lhs(std::move(lhs)), m_rhs(std::move(rhs)) {}

std::string BinaryOpExprAST::toString() {
    std::stringstream ss;
    ss << "(" << m_lhs->toString() << ", " << (int)m_operator << ", " << m_rhs->toString() << ")";
    return ss.str();
}

Value BinaryOpExprAST::evaluate(Environment& env) {
    switch(m_operator) {
        case Operator::EQ:
            return Value(m_lhs -> evaluate(env) == m_rhs -> evaluate(env) ? 1.0 : 0.0);
        case Operator::NEQ:
            return Value(m_lhs -> evaluate(env) != m_rhs -> evaluate(env) ? 1.0 : 0.0);
        case Operator::ADD:
            return Value(m_lhs -> evaluate(env) + m_rhs -> evaluate(env));
        case Operator::SUB:
            return Value(m_lhs -> evaluate(env) - m_rhs -> evaluate(env));
        case Operator::MUL:
            return Value(m_lhs -> evaluate(env) * m_rhs -> evaluate(env));
        case Operator::DIV:
            return Value(m_lhs -> evaluate(env) / m_rhs -> evaluate(env));
        case Operator::DIV_FLR:
            return Value(m_lhs -> evaluate(env).divFloor(m_rhs -> evaluate(env)));
        case Operator::POW:
            return Value(m_lhs -> evaluate(env).power(m_rhs -> evaluate(env)));
        default:
            return Value();
    }
}
