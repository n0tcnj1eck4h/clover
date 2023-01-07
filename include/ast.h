#pragma once
#include <string>
#include <vector>
#include <memory>
#include "types.h"
#include "enums.h"
#include "value.h"


class ASTVisitor;


class ASTNode {
	public:
		virtual ~ASTNode();
		virtual std::string toString() = 0;
};


class ExprAST : public ASTNode {
	public:
		virtual ~ExprAST();
};


class LiteralAST : public ExprAST {
	Value m_value;

public:
	LiteralAST(const Value& value);
		virtual std::string toString() override;
};


class VariableExprAST : public ExprAST {
	std::string m_name;

public:
	VariableExprAST(const std::string& name);
	virtual std::string toString() override;
};


class BinaryOpExprAST : public ExprAST {
	Operator m_operator;
	std::unique_ptr<ExprAST> m_lhs;
	std::unique_ptr<ExprAST> m_rhs; 

public:
	BinaryOpExprAST(Operator op, std::unique_ptr<ExprAST>& lhs, std::unique_ptr<ExprAST>& rhs); 
	virtual std::string toString() override;
};


class CallExprAST : public ExprAST {
	std::string m_callee;
	std::vector<std::unique_ptr<ExprAST>> m_args;

public:
	CallExprAST(std::string& callee, std::vector<std::unique_ptr<ExprAST>> args);
	virtual std::string toString() override;
};


class PrototypeAST : public ASTNode {
	std::string m_name;
	std::vector<std::string> m_args;

public:
	PrototypeAST(std::string& name, std::vector<std::string>& args);
	virtual std::string toString() override;
	const std::string& getName() const;
};


class FunctionAST : public ASTNode {
	std::unique_ptr<PrototypeAST> m_prototype;
	std::unique_ptr<ExprAST> m_body;

public:
	FunctionAST(std::unique_ptr<PrototypeAST> prototype, std::unique_ptr<ExprAST> body);
	virtual std::string toString() override;
};

