#pragma once
#include "ast/ast.h"

class LiteralAST : public ExprAST {
	Value m_value;

public:
	LiteralAST(const Value& value);
	virtual std::string toString() override;
	virtual Value evaluate(Environment& env) override;
};
