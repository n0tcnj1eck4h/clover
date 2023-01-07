#include "token.h"
#include "errors.h"
#include <sstream>
#include <variant>

Token::Token(const Token::Variant& data) : m_data(data) {}

Token::Type Token::getType() const {
	return (Token::Type)m_data.index();
}

bool Token::operator==(const Token& t) const {
	return m_data == t.m_data;
}

// bool Token::matchAtom(char atom) {
// 	auto a = std::get_if<Atom>(&m_data);
// 	return getType() == Token::Type::Atom && a && a->atom == atom;
// }

// bool Token::matchKeyword(Keyword keyword) {
// 	auto k = std::get_if<Token::Keyword>(&m_data);
// 	bool match = getType() == Token::Type::Keyword && k && *k == keyword;
// 	if(false && !match) {
// 		std::stringstream ss;
// 		ss << "Keyword(" << (u8)keyword << ")";
// 		throw UnexpectedTokenException(*this, ss.str());
// 	}
// 	else return match;
// }
//
// bool Token::getValue(f64& decimal, bool should_throw) {
// 	auto v = std::get_if<f64>(&m_data);
// 	if(v) {
// 		decimal = *v;
// 		return true;
// 	} 
//
// 	if(should_throw) throw UnexpectedTokenException(*this, "Decimal");
// 	return false;
// }
//
// bool Token::getValue(Atom& atom, bool should_throw) {
// 	auto v = std::get_if<Atom>(&m_data);
// 	if(v) {
// 		atom = *v;
// 		return true;
// 	} 
//
// 	if(should_throw) throw UnexpectedTokenException(*this, "Atom");
// 	return false;
// }
//
// bool Token::getValue(i64& integer, bool should_throw) {
// 	auto v = std::get_if<i64>(&m_data);
// 	if(v) {
// 		integer = *v;
// 		return true;
// 	} 
//
// 	if(should_throw) throw UnexpectedTokenException(*this, "Integer");
// 	return false;
// }
//
// bool Token::getValue(Identifier& identifier, bool should_throw) {
// 	auto v = std::get_if<Identifier>(&m_data);
// 	if(v) {
// 		identifier = *v;
// 		return true;
// 	} 
//
// 	if(should_throw) throw UnexpectedTokenException(*this, "Identifier");
// 	return false;
// }

std::string Token::toString() const {
	std::stringstream ss;
	switch (getType()) {
    case Token::Type::EndOfFile:
    	ss << "EndOfFile";
    	break;

    case Token::Type::Identifier:
    	ss << "Identifier(" << std::get<Identifier>(m_data) << ')';
    	break;

    case Token::Type::Keyword:
			ss << "Keyword(" << (i32)std::get<Keyword>(m_data) << ")";
    	break;

    case Token::Type::Operator:
    	ss << "Operator(" << (i32)std::get<Operator>(m_data) << ")";
    	break;

    case Token::Type::Literal:
    	ss << "Literal(" << std::get<Literal>(m_data).toString() << ")";
    	break;

    case Token::Type::Atom:
    	ss << "Atom(\"" << (u32)std::get<Atom>(m_data) << "\")";
    	break;
  }

  return ss.str();
}

