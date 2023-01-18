#pragma once
#include "ast/AST.h"

class LiteralAST : public ExprAST {
	Value m_value;

public:
	LiteralAST(const Value& value);
	virtual std::string toString() override;
	virtual Value evaluate() override;
};
