#pragma once
#include "ast/ast.h"

class BinaryOpExprAST : public ExprAST {
	Operator m_operator;
	std::unique_ptr<ExprAST> m_lhs;
	std::unique_ptr<ExprAST> m_rhs; 

public:
	BinaryOpExprAST(Operator op, std::unique_ptr<ExprAST>& lhs, std::unique_ptr<ExprAST>& rhs); 
	virtual std::string toString() override;
	virtual Value evaluate() override;
};
