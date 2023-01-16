#include "parser.h"
#include "ast/AST.h"
#include "ast/literalAST.h"
#include "ast/binopAST.h"
#include "ast/callAST.h"
#include "ast/variableAST.h"
#include "token.h"
#include "errors.h"
#include <memory>
#include <iostream>
#include <mutex>
#include <utility>
#include <variant>

void Parser::expect(const Token val) {
  if(m_current_token != val) {
    throw UnexpectedTokenException(m_current_token, val.toString());
  }
  getNextToken();
}

void Parser::expect(const Token::Type type) {
    if(m_current_token.getType() != type) {
        throw UnexpectedTokenException(m_current_token, "");
    }
}

bool Parser::match(const Token val) {
  if(m_current_token != val) 
    return false;

  getNextToken();
  return true;
}

Parser::Parser(Lexer &lexer)
    : m_lexer(lexer), m_current_token(lexer.getToken()){};

Token &Parser::getNextToken() {
  m_current_token = m_lexer.getToken();
  return m_current_token;
}

// numberexp ::= number
std::unique_ptr<ExprAST> Parser::parseLiteralExpr() {
    Value decimal = m_current_token.get<Token::Literal>();
    getNextToken();
    return std::make_unique<LiteralAST>(Value(decimal));
}

// parenexpr ::= '(' expression ')'
std::unique_ptr<ExprAST> Parser::parseParenExpr() {
    expect(Token(Atom::PAREN_OPEN));
    auto exp = parseExpression();
    expect(Token(Atom::PAREN_CLOSE));
    return exp;
}

// identifierexpr
//   ::= identifier
//   ::= identifier '(' expression* ')'
std::unique_ptr<ExprAST> Parser::parseIdentifierExpr() {
    Token::Identifier identifier = m_current_token.get<Token::Identifier>();
    getNextToken();
  
    // Try parsing a function call
    if (match(Token(Atom::PAREN_OPEN))) {
      std::vector<std::unique_ptr<ExprAST>> args;
  
      do {
        args.push_back(parseExpression());
      } while (match(Token(Atom::COMMA)));
  
      expect(Token(Atom::PAREN_CLOSE));
  
      return std::make_unique<CallExprAST>(identifier, std::move(args));
    }
  
    return std::make_unique<VariableExprAST>(identifier);
}

std::unique_ptr<ExprAST> Parser::parseExpression() {
  auto lhs = parsePrimary();
  if (!lhs)
    throw;
   return parseRHSBinaryExpr(0, std::move(lhs));
}

// primary
//   ::= identifierexpr
//   ::= numberexpr
//   ::= parenexpr
std::unique_ptr<ExprAST> Parser::parsePrimary() {
  switch (m_current_token.getType()) {
  case Token::Type::Identifier:
    return parseIdentifierExpr();

  case Token::Type::Literal:
    return parseLiteralExpr();

  case Token::Type::Atom:
    if (m_current_token == Token(Atom::PAREN_OPEN))
      return parseParenExpr();
    else throw UnexpectedTokenException(m_current_token, "(");

  default:
    throw UnexpectedTokenException(m_current_token, "Identifier, Integer, Decimal or Atom");
  }
}

// rhsbinexpr 
//   ::= ( '+' primary )*
std::unique_ptr<ExprAST>
Parser::parseRHSBinaryExpr(i32 exprPrecedence, std::unique_ptr<ExprAST> lhs) {
  while (true) {
    if(m_current_token.getType() != Token::Type::Operator) {
      return lhs;
    }

    Operator op = m_current_token.get<Operator>();

    i32 tokenPrecedence = getOperatorPrecedence(op);

    if (exprPrecedence > tokenPrecedence)
      return lhs;

    getNextToken();

    auto rhs = parsePrimary();
    if (!rhs)
      return nullptr;

    i32 nextTokenPrecedence = -1;
    if(m_current_token.getType() == Token::Type::Operator) {
      Operator next_op = m_current_token.get<Operator>();
      nextTokenPrecedence = getOperatorPrecedence(next_op);
    }

    if (tokenPrecedence < nextTokenPrecedence) {
      rhs = parseRHSBinaryExpr(exprPrecedence + 1, std::move(rhs));
      if (!rhs)
        return nullptr;
    }

    lhs = std::make_unique<BinaryOpExprAST>(op, lhs, rhs);
  }
}

std::unique_ptr<PrototypeAST> Parser::parsePrototype() {
    Token::Identifier identifier = m_current_token.get<Token::Identifier>();
    getNextToken();

    expect(Token(Atom::PAREN_OPEN));

    std::vector<std::string> args;

    while(getNextToken().getType() == Token::Type::Identifier) {
      Token::Identifier arg = m_current_token.get<Token::Identifier>();
      args.push_back(arg);
    }

    expect(Token(Atom::PAREN_CLOSE));

    return std::make_unique<PrototypeAST>(identifier, args);
}

i32 Parser::getOperatorPrecedence(Operator op) {
    switch (op) {
    case Operator::ADD:
    case Operator::SUB:
      return 10;
    
    case Operator::MUL:
    case Operator::DIV:
    case Operator::DIV_FLR:
      return 20;

    case Operator::POW:
      return 30;
    
    default:
      return -1;
    }
}

