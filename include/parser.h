#pragma once
#include "ast/ast.h"
#include "lexer.h"
#include "token.h"
#include <vector>
#include <memory>

class Parser {
  Lexer &m_lexer;
  Token m_current_token;
  Token &getNextToken();

public:
  Parser(Lexer &lexer);
  std::vector<std::unique_ptr<StmtAST>> parse();
  std::unique_ptr<StmtAST> parseDeclaration();
  std::unique_ptr<StmtAST> parseStatement();
  std::unique_ptr<StmtAST> parseBlock();
  std::unique_ptr<ExprAST> parseLiteralExpr();
  std::unique_ptr<ExprAST> parseParenExpr();
  std::unique_ptr<ExprAST> parseIdentifierExpr();
  std::unique_ptr<ExprAST> parseExpression();
  std::unique_ptr<ExprAST> parsePrimary();
  std::unique_ptr<ExprAST> parseRHSBinaryExpr(i32 exprPrecedence, std::unique_ptr<ExprAST> lhs); 
  std::unique_ptr<PrototypeAST> parsePrototype();

  bool match(const Token val);
  void expect(const Token val);
  void expect(const Token::Type type);

  static i32 getOperatorPrecedence(Operator op);
};



