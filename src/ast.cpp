#include <sstream>
#include "ast/ast.h"

ASTNode::~ASTNode() {}
ExprAST::~ExprAST() {}
StmtAST::~StmtAST() {}

PrototypeAST::PrototypeAST(std::string& name, std::vector<std::string>& args)
    : m_name(name), m_args(std::move(args)) {}


FunctionAST::FunctionAST(std::unique_ptr<PrototypeAST> prototype, std::unique_ptr<ExprAST> body) 
    : m_prototype(std::move(prototype)), m_body(std::move(body)) {}

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
