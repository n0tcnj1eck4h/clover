#pragma once
#include "ast/AST.h"

class CallExprAST : public ExprAST {
	std::string m_callee;
	std::vector<std::unique_ptr<ExprAST>> m_args;

public:
	CallExprAST(std::string& callee, std::vector<std::unique_ptr<ExprAST>> args);
	virtual std::string toString() override;
	virtual Value evaluate() override;
};
