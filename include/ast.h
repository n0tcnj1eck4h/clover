#pragma once
#include <string>
#include <vector>
#include <memory>
#include "types.h"
#include "operators.h"

class ExprAST {
	public:
		virtual ~ExprAST();
		virtual std::string toString() = 0;
};

class IntegerLiteralAST : public ExprAST {
	i64 m_value;

public:
	IntegerLiteralAST(i64 value);
	virtual std::string toString() override;
};

class DecimalLiteralAST : public ExprAST {
	f64 m_value;

public:
	DecimalLiteralAST(f64 value);
	virtual std::string toString() override;
};

class VariableExprAST : public ExprAST {
	std::string m_name;
public:
	VariableExprAST(const std::string& name);
	virtual std::string toString() override;
};

class BinaryOpExprAST : public ExprAST {
	char m_operator;
	std::unique_ptr<ExprAST> m_lhs;
	std::unique_ptr<ExprAST> m_rhs; 
public:
	BinaryOpExprAST(char op, std::unique_ptr<ExprAST>& lhs, std::unique_ptr<ExprAST>& rhs); 
	virtual std::string toString() override;
};

class CallExprAST : public ExprAST {
	std::string m_callee;
	std::vector<std::unique_ptr<ExprAST>> m_args;

public:
	CallExprAST(std::string& callee, std::vector<std::unique_ptr<ExprAST>> args);
	virtual std::string toString() override;
};

class PrototypeAST {
	std::string m_name;
	std::vector<std::string> m_args;

public:
	PrototypeAST(std::string& name, std::vector<std::string>& args);
	const std::string& getName() const;
	std::string toString();
};

class FunctionAST {
	std::unique_ptr<PrototypeAST> m_prototype;
	std::unique_ptr<ExprAST> m_body;

public:
	FunctionAST(std::unique_ptr<PrototypeAST> prototype, std::unique_ptr<ExprAST> body);
	std::string toString();
};

