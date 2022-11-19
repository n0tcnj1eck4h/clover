#include "ast.h"

ExprAST::~ExprAST() {}

NumberValAST::NumberValAST(i64 value) : m_value(value) {}

VariableExprAST::VariableExprAST(const std::string& name) : m_name(name) {}

BinaryOpExpression::BinaryOpExpression(char op, std::unique_ptr<ExprAST>& lhs, std::unique_ptr<ExprAST>& rhs)
    : m_operator(op), m_lhs(std::move(lhs)), m_rhs(std::move(rhs)) {}

CallExprAST::CallExprAST(std::string& callee, std::vector<std::unique_ptr<ExprAST>> args)
    : m_callee(callee), m_args(std::move(args)) {}


PrototypeAST::PrototypeAST(std::string& name, std::vector<std::string>& args)
    : m_name(name), m_args(std::move(args)) {}


FunctionAST::FunctionAST(std::unique_ptr<PrototypeAST> prototype, std::unique_ptr<ExprAST> body) 
    : m_prototype(std::move(prototype)), m_body(std::move(body)) {}
