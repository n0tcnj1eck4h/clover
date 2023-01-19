#pragma once
#include "ast/ast.h"

class InputExprAST : public ExprAST {
public:
	virtual Value evaluate(Environment& env) override;
};
