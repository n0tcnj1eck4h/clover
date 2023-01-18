#include "ast/callExprAST.h"
#include "sstream"

CallExprAST::CallExprAST(std::string& callee, std::vector<std::unique_ptr<ExprAST>> args)
    : m_callee(callee), m_args(std::move(args)) {}

std::string CallExprAST::toString() {
    std::stringstream ss;
    ss << "<CallExpr (" << m_callee;
    for (const auto& arg : m_args)
        ss << arg << ", ";
    ss << ")>";
    return ss.str();
}

Value CallExprAST::evaluate() {
    return Value(1.0);
}
