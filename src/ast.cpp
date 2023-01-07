#include <sstream>
#include "ast.h"

ASTNode::~ASTNode() {}
ExprAST::~ExprAST() {}


LiteralAST::LiteralAST(const Value& value) : m_value(value) {}


VariableExprAST::VariableExprAST(const std::string& name) : m_name(name) {}


BinaryOpExprAST::BinaryOpExprAST(Operator op, std::unique_ptr<ExprAST>& lhs, std::unique_ptr<ExprAST>& rhs)
    : m_operator(op), m_lhs(std::move(lhs)), m_rhs(std::move(rhs)) {}


CallExprAST::CallExprAST(std::string& callee, std::vector<std::unique_ptr<ExprAST>> args)
    : m_callee(callee), m_args(std::move(args)) {}


PrototypeAST::PrototypeAST(std::string& name, std::vector<std::string>& args)
    : m_name(name), m_args(std::move(args)) {}


FunctionAST::FunctionAST(std::unique_ptr<PrototypeAST> prototype, std::unique_ptr<ExprAST> body) 
    : m_prototype(std::move(prototype)), m_body(std::move(body)) {}


std::string LiteralAST::toString() {
    std::stringstream ss;
    ss << "<Value " << m_value.toString() << ">";
    return ss.str();
}

std::string VariableExprAST::toString() {
    std::stringstream ss;
    ss << "<Variable " << m_name << ">";
    return ss.str();
}

std::string BinaryOpExprAST::toString() {
    std::stringstream ss;
    ss << "<BinExpr " << m_lhs->toString() << ", " << (int)m_operator << ", " << m_rhs->toString() << ">";
    return ss.str();
}

std::string CallExprAST::toString() {
    std::stringstream ss;
    ss << "<CallExpr (" << m_callee;
    for (const auto& arg : m_args)
        ss << arg << ", ";
    ss << ")>";
    return ss.str();
}

std::string PrototypeAST::toString() {
    std::stringstream ss;
    ss << "<Prototype (" << m_name;
    for (const auto& arg : m_args)
        ss << arg << ", ";
    ss << ")>";
    return ss.str();
}

std::string FunctionAST::toString() {
    std::stringstream ss;
    ss << "<Function " << m_prototype->toString() << ", " << m_body->toString() << ">";
    return ss.str();
}
