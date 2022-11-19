#pragma once
#include "ast.h"
#include "lexer.h"
#include "token.h"
#include <memory>

class Parser {
  Lexer &m_lexer;
  Token m_current_token;
  Token &getNextToken();

public:
  Parser(Lexer &lexer);
  std::unique_ptr<ExprAST> parseNumberExpr();
  std::unique_ptr<ExprAST> parseParenExpr();
  std::unique_ptr<ExprAST> parseIdentifierExpr();
  std::unique_ptr<ExprAST> parseExpression();
  std::unique_ptr<ExprAST> parsePrimary();
  std::unique_ptr<ExprAST> parseRHSBinaryExpr(i32 exprPrecedence, std::unique_ptr<ExprAST> lhs); 

  static i32 getOperatorPrecedence(char op);
};
