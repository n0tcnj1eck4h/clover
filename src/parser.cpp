#include "parser.h"
#include "ast.h"
#include "token.h"
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
  if (m_current_token.getValue(integer)) {
    auto result = std::make_unique<NumberValAST>(integer);
    getNextToken();
    return result;
  }

  throw;
}

// parenexpr ::= '(' expression ')'
std::unique_ptr<ExprAST> Parser::parseParenExpr() {
  if (!m_current_token.matchAtom('('))
    throw;
  getNextToken();

  auto exp = parseExpression();

  if (!m_current_token.matchAtom(')'))
    throw;
  getNextToken();

  return exp;
}

// identifierexpr
//   ::= identifier
//   ::= identifier '(' expression* ')'
std::unique_ptr<ExprAST> Parser::parseIdentifierExpr() {
  std::string identifier;

  if (!m_current_token.getValue(identifier))
    throw;
  getNextToken();

  // Try parsing a function call
  if (m_current_token.matchAtom('(')) {
    std::vector<std::unique_ptr<ExprAST>> args;

    do {
      getNextToken();
      args.push_back(parseExpression());
    } while (m_current_token.matchAtom(','));

    if (!m_current_token.matchAtom(')'))
      throw;
    getNextToken();

    return std::make_unique<CallExprAST>(identifier, std::move(args));
  }

  // otherwise return a simple variable reference
  return std::make_unique<VariableExprAST>(identifier);
}

std::unique_ptr<ExprAST> Parser::parseExpression() {
  auto lhs = parsePrimary();
  if (!lhs)
    throw;
  // return parseRHSBinaryExpr();
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
    return parseNumberExpr();
  case Token::Type::Atom:
    if (m_current_token.matchAtom('('))
      return parseParenExpr();

  default:
    throw;
  }
}

std::unique_ptr<ExprAST>
Parser::parseRHSBinaryExpr(i32 exprPrecedence, std::unique_ptr<ExprAST> lhs) {

  while (true) {
    char op;
    if (!m_current_token.getValue(op))
      throw;

    i32 tokenPrecedence = getOperatorPrecedence(op);

    if (exprPrecedence > tokenPrecedence)
      return lhs;

    getNextToken();

    auto rhs = parsePrimary();
    if (!rhs)
      return nullptr;

    char next_op;
    if (!m_current_token.getValue(next_op))
      throw;

    i32 nextTokenPrecedence = getOperatorPrecedence(next_op);
    if (tokenPrecedence < nextTokenPrecedence) {
      rhs = parseRHSBinaryExpr(exprPrecedence + 1, std::move(rhs));
      if (!rhs)
        return nullptr;
    }

    lhs = std::make_unique<BinaryOpExpression>(op, lhs, rhs);
  }
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
