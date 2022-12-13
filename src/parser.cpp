#include "parser.h"
#include "ast.h"
#include "token.h"
#include "errors.h"
#include <memory>
#include <mutex>
#include <utility>
#include <variant>

Parser::Parser(Lexer &lexer)
    : m_lexer(lexer), m_current_token(lexer.getToken()){};

Token &Parser::getNextToken() {
  m_current_token = m_lexer.getToken();
  return m_current_token;
}

// numberexp ::= number
std::unique_ptr<ExprAST> Parser::parseNumberExpr() {
  i64 integer;
  f64 decimal;
  if (m_current_token.getValue(integer, false)) {
    auto result = std::make_unique<IntegerLiteralAST>(integer);
    getNextToken();
    return result;
  }

  if (m_current_token.getValue(decimal, false)) {
    auto result = std::make_unique<IntegerLiteralAST>(decimal);
    getNextToken();
    return result;
  }

  throw UnexpectedTokenException(m_current_token, "Integer literal");
}

// parenexpr ::= '(' expression ')'
std::unique_ptr<ExprAST> Parser::parseParenExpr() {
  if (!m_current_token.matchAtom('(')) throw UnexpectedTokenException(m_current_token, "(");
  getNextToken();

  auto exp = parseExpression();

  if (!m_current_token.matchAtom(')')) throw UnexpectedTokenException(m_current_token, ")");
  getNextToken();

  return exp;
}

// identifierexpr
//   ::= identifier
//   ::= identifier '(' expression* ')'
std::unique_ptr<ExprAST> Parser::parseIdentifierExpr() {
    Token::Identifier identifier;

  m_current_token.getValue(identifier);
  getNextToken();

  // Try parsing a function call
  if (m_current_token.matchAtom('(')) {
    std::vector<std::unique_ptr<ExprAST>> args;

    do {
      getNextToken();
      args.push_back(parseExpression());
    } while (m_current_token.matchAtom(','));

    if (!m_current_token.matchAtom(')')) throw UnexpectedTokenException(m_current_token, ")");
    getNextToken();

    return std::make_unique<CallExprAST>(identifier.identifier, std::move(args));
  }

  // otherwise return a simple variable reference
  return std::make_unique<VariableExprAST>(identifier.identifier);
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

  case Token::Type::Integer:
  case Token::Type::Decimal:
    return parseNumberExpr();

  case Token::Type::Atom:
    if (m_current_token.matchAtom('('))
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
    Token::Atom op;
    m_current_token.getValue(op);

    i32 tokenPrecedence = getOperatorPrecedence(op.atom);

    if (exprPrecedence > tokenPrecedence)
      return lhs;

    getNextToken();

    auto rhs = parsePrimary();
    if (!rhs)
      return nullptr;

    Token::Atom next_op;
    m_current_token.getValue(next_op);

    i32 nextTokenPrecedence = getOperatorPrecedence(next_op.atom);
    if (tokenPrecedence < nextTokenPrecedence) {
      rhs = parseRHSBinaryExpr(exprPrecedence + 1, std::move(rhs));
      if (!rhs)
        return nullptr;
    }

    lhs = std::make_unique<BinaryOpExpression>(op.atom, lhs, rhs);
  }
}

std::unique_ptr<PrototypeAST> Parser::parsePrototype() {
    Token::Identifier identifier;
    m_current_token.getValue(identifier);
    getNextToken();

    if (!m_current_token.matchAtom('(')) throw UnexpectedTokenException(m_current_token, "(");

    std::vector<std::string> args;
    Token::Identifier arg;
    
    while(getNextToken().getType() == Token::Type::Identifier) {
        m_current_token.getValue(arg);
        args.push_back(arg.identifier);
    }

    if (!m_current_token.matchAtom(')')) throw UnexpectedTokenException(m_current_token, ")");
    getNextToken();

    return std::make_unique<PrototypeAST>(identifier.identifier, args);
}

i32 Parser::getOperatorPrecedence(char op) {
  switch (op) {
  case '+':
  case '-':
    return 10;

  case '*':
  case '/':
    return 20;

  default:
    return -1;
  }
}

