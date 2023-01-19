#include "parser.h"
#include "ast/ast.h"
#include "ast/expr/literalExprAST.h"
#include "ast/expr/binopExprAST.h"
#include "ast/expr/callExprAST.h"
#include "ast/expr/variableExprAST.h"
#include "ast/stmt/printStmtAST.h"
#include "ast/stmt/vardeclStmtAST.h"
#include "ast/stmt/exprStmtAST.h"
#include "ast/stmt/blockStmtAST.h"
#include "ast/stmt/conditionalStmtAST.h"
#include "ast/stmt/maybeStmtAST.h"
#include "ast/stmt/crashStmtAST.h"
#include "ast/stmt/whileStmtAST.h"
#include "enums.h"
#include "token.h"
#include "errors.h"
#include <memory>
#include <iostream>
#include <mutex>
#include <utility>
#include <variant>

Parser::Parser(Lexer &lexer)
    : m_lexer(lexer), m_current_token(lexer.getToken()){};

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

Token &Parser::getNextToken() {
  m_current_token = m_lexer.getToken();
  return m_current_token;
}

std::vector<std::unique_ptr<StmtAST>> Parser::parse() {
  std::vector<std::unique_ptr<StmtAST>> statements;
  while(m_current_token.getType() != Token::Type::EndOfFile) {
    statements.push_back(parseDeclaration());
  }

  return statements;
}

std::unique_ptr<StmtAST> Parser::parseDeclaration() {
  if(match(Token(Keyword::SET))) {
    std::unique_ptr<ExprAST> e;
    std::string identifier = m_current_token.get<Token::Identifier>();
    getNextToken();

    if(match(Token(Operator::ASSIGN))) {
      e = parseExpression();
    }

    expect(Token(Atom::END_STATEMENT));
    return std::make_unique<VardeclStmtAST>(identifier, e);
  }

  return parseStatement();
}

std::unique_ptr<StmtAST> Parser::parseStatement() {
  if(match(Token(Keyword::PRINT))) {
    auto expr = parseExpression();
    expect(Token(Atom::END_STATEMENT));
    return std::make_unique<PrintStmtAST>(expr);
  }

  if(match(Token(Atom::BLOCK_OPEN)))
      return parseBlock();
  
  if(match(Token(Keyword::IF))) {
      return parseConditional();
  }
  
  if(match(Token(Keyword::WHILE))) {
      auto condition = parseExpression();
      auto body = parseStatement();
      return std::make_unique<WhileStmtAST>(body, condition);
  }

  if(match(Token(Keyword::CRASH))) {
    expect(Token(Atom::END_STATEMENT));
    return std::make_unique<CrashStmtAST>();
  }

  if(match(Token(Keyword::MAYBE))) {
      auto stmt = parseStatement();
      return std::make_unique<MaybeStmtAST>(stmt);
  }

  auto expr = parseExpression();
  expect(Token(Atom::END_STATEMENT));

  return std::make_unique<ExprStmtAST>(expr);
}

std::unique_ptr<StmtAST> Parser::parseConditional() {
    auto condition = parseExpression();
    auto statements = parseStatement();

    if(match(Token(Keyword::ELSE))) {
        auto else_statements = parseStatement();
        return std::make_unique<ConditionalStmtAST>(condition, statements, else_statements);
    }

    return std::make_unique<ConditionalStmtAST>(condition, statements);
}

std::unique_ptr<StmtAST> Parser::parseBlock() {
  std::vector<std::unique_ptr<StmtAST>> statements;
  do {
    statements.push_back(parseDeclaration());
  } while(!match(Token(Atom::BLOCK_CLOSE)));

  return std::make_unique<BlockStmtAST>(statements);
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
    else throw UnexpectedTokenException(m_current_token, "Expression");

  default:
    throw UnexpectedTokenException(m_current_token, "Expression");
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

    case Operator::EQ:
      return 10;

    case Operator::GTR:
    case Operator::GTQ:
    case Operator::LESS:
    case Operator::LTQ:
      return 10;

    case Operator::ASSIGN:
      return 0;
    
    default:
      return -1;
    }
}

