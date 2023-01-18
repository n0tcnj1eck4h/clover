#pragma once
#include "ast/ast.h"

class VariableExprAST : public ExprAST {
	std::string m_name;

public:
	VariableExprAST(const std::string& name);
	virtual std::string toString() override;
	virtual Value evaluate(Environment& env) override;
};
