#pragma once
#include <memory>
#include "ast.h"
#include "lexer.h"
#include "token.h"

class Parser {
	Lexer& m_lexer;
    Token m_current_token;   
    Token& getNextToken();

public:
    Parser(Lexer& lexer);
    std::unique_ptr<ExprAST> parseNumberExpr();
    std::unique_ptr<ExprAST> parseParenExpr();
    std::unique_ptr<ExprAST> parseIdentifierExpr();
    std::unique_ptr<ExprAST> parseExpression();
};

