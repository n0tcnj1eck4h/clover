#pragma once
#include <string>
#include <vector>
#include <memory>
#include "types.h"
#include "enums.h"
#include "value.h"


class ASTNode {
	public:
		virtual ~ASTNode();
		virtual std::string toString() = 0;
};

class StmtAST : public ASTNode {
	public:
		virtual ~StmtAST();
		virtual void evaluate() = 0;
};

class ExprAST : public ASTNode {
	public:
		virtual ~ExprAST();
		virtual Value evaluate() = 0;
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

