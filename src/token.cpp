#include "token.h"
#include "errors.h"
#include <sstream>
#include <variant>

Token::Token(Token::Type type) : m_type(type), m_data() { }
Token::Token(Atom atom) : m_type(Token::Type::Atom), m_data(atom) { }
Token::Token(f64 decimal) : m_type(Token::Type::Decimal), m_data(decimal) { }
Token::Token(i64 integer) : m_type(Token::Type::Integer), m_data(integer) { }
Token::Token(Keyword keyword) : m_type(Token::Type::Keyword), m_data(keyword) { }
Token::Token(const Identifier& identifier) : m_type(Token::Type::Identifier), m_data(identifier) { }

Token::Type Token::getType() const {
	return m_type;
}

bool Token::matchAtom(char atom) {
	auto a = std::get_if<Atom>(&m_data);
	return m_type == Token::Type::Atom && a && a->atom == atom;
}

bool Token::matchKeyword(Keyword keyword) {
	auto k = std::get_if<Token::Keyword>(&m_data);
	bool match = m_type == Token::Type::Keyword && k && *k == keyword;
	if(false && !match) {
		std::stringstream ss;
		ss << "Keyword(" << (u8)keyword << ")";
		throw UnexpectedTokenException(*this, ss.str());
	}
	else return match;
}

bool Token::getValue(f64& decimal, bool should_throw) {
	auto v = std::get_if<f64>(&m_data);
	if(v) {
		decimal = *v;
		return true;
	} 

	if(should_throw) throw UnexpectedTokenException(*this, "Decimal");
	return false;
}

bool Token::getValue(Atom& atom, bool should_throw) {
	auto v = std::get_if<Atom>(&m_data);
	if(v) {
		atom = *v;
		return true;
	} 

	if(should_throw) throw UnexpectedTokenException(*this, "Atom");
	return false;
}

bool Token::getValue(i64& integer, bool should_throw) {
	auto v = std::get_if<i64>(&m_data);
	if(v) {
		integer = *v;
		return true;
	} 

	if(should_throw) throw UnexpectedTokenException(*this, "Integer");
	return false;
}

bool Token::getValue(Identifier& identifier, bool should_throw) {
	auto v = std::get_if<Identifier>(&m_data);
	if(v) {
		identifier = *v;
		return true;
	} 

	if(should_throw) throw UnexpectedTokenException(*this, "Identifier");
	return false;
}

std::string Token::toString() const {
	std::stringstream ss;
	switch (m_type) {
    case Token::Type::EndOfFile:
    	ss << "EndOfFile";
    	break;

    case Token::Type::Integer:
    	ss << "Integer(" << std::get<i64>(m_data) << ')';
    	break;

    case Token::Type::Decimal:
    	ss << "Float(" << std::get<f64>(m_data) << ')';
    	break;

    case Token::Type::Identifier:
    	ss << "Identifier(" << std::get<Identifier>(m_data).identifier << ')';
    	break;

    case Token::Type::Keyword:
			ss << "Keyword(" << (u8)std::get<Keyword>(m_data) << ")";
    	break;

    case Token::Type::Atom:
    	ss << "Atom('" << std::get<Atom>(m_data).atom << "')";
    	break;
  }

  return ss.str();
}

