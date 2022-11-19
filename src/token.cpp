#include "token.h"
#include <variant>

Token::Token(Token::Type type) : m_type(type), m_data() { }
Token::Token(char atom) : m_type(Token::Type::Atom), m_data(atom) { }
Token::Token(f64 decimal) : m_type(Token::Type::Float), m_data(decimal) { }
Token::Token(i64 integer) : m_type(Token::Type::Integer), m_data(integer) { }
Token::Token(Keyword keyword) : m_type(Token::Type::Keyword), m_data(keyword) { }
Token::Token(const std::string& identifier) : m_type(Token::Type::Identifier), m_data(identifier) { }

Token::Type Token::getType() const {
	return m_type;
}

bool Token::matchAtom(char atom) {
	auto a = std::get_if<char>(&m_data);
	return m_type == Token::Type::Atom && a && *a == atom;
}

bool Token::matchKeyword(Keyword keyword) {
	auto k = std::get_if<Token::Keyword>(&m_data);
	return m_type == Token::Type::Keyword && k && *k == keyword;
}

bool Token::getValue(f64& decimal) {
	auto v = std::get_if<f64>(&m_data);
	if(v) {
		decimal = *v;
		return true;
	} 

	return false;
}

bool Token::getValue(char& atom) {
	auto v = std::get_if<char>(&m_data);
	if(v) {
		atom = *v;
		return true;
	} 

	return false;
}

bool Token::getValue(i64& integer) {
	auto v = std::get_if<i64>(&m_data);
	if(v) {
		integer = *v;
		return true;
	} 

	return false;
}

bool Token::getValue(std::string& identifier) {
	auto v = std::get_if<std::string>(&m_data);
	if(v) {
		identifier = *v;
		return true;
	} 

	return false;
}
