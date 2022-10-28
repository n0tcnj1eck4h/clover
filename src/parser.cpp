#include "parser.h"
#include "ast.h"
#include "token.h"
#include <memory>
#include <utility>
#include <variant>

Parser::Parser(Lexer& lexer) : m_lexer(lexer), m_current_token(lexer.getToken()) {};

TokenVariant& Parser::getNextToken() {
	m_current_token = m_lexer.getToken();
	return m_current_token;
}

// numberexp ::= number
std::unique_ptr<ExprAST> Parser::parseNumberExpr() {
	auto token = std::get<Token::Number>(m_current_token);
	auto result = std::make_unique<NumberValAST>(token.value);
	getNextToken();
	return result;
}

// parenexpr ::= '(' expression ')'
std::unique_ptr<ExprAST> Parser::parseParenExpr() {
    auto paren1 = std::get<Token::Atom>(m_current_token);
    if(paren1.atom != Token::AtomEnum::PARENTHESIS_OPEN) throw;
    getNextToken();

    auto exp = parseExpression();
    // TODO: error check?

    auto paren2 = std::get<Token::Atom>(m_current_token);
    if(paren2.atom != Token::AtomEnum::PARENTHESIS_CLOSE) throw;
    getNextToken();
    
    return exp;
}


// identifierexpr
//   ::= identifier
//   ::= identifier '(' expression* ')'
std::unique_ptr<ExprAST> Parser::parseIdentifierExpr() {
	// Get the identifier
	auto identifier = std::get<Token::Identifier>(m_current_token);
    getNextToken();
	
	// Try parsing a function call
	auto a = std::get_if<Token::Atom>(&m_current_token);
	if(a != nullptr) {
        if(a -> atom != Token::AtomEnum::PARENTHESIS_OPEN) throw;
		std::vector<std::unique_ptr<ExprAST>> args;
		do {
            getNextToken();
            args.push_back(parseExpression());
        } while((a = std::get_if<Token::Atom>(&m_current_token)) && a -> atom == Token::AtomEnum::COMMA);
        if(a -> atom != Token::AtomEnum::PARENTHESIS_CLOSE) throw;
        getNextToken();

        return std::make_unique<CallExprAST>(identifier.name, std::move(args));
	}

	// otherwise return a simple variable reference
	return std::make_unique<VariableExprAST>(identifier.name);
}

std::unique_ptr<ExprAST> Parser::parseExpression() {
	return nullptr;
}
