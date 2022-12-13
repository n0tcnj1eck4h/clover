#include "lexer.h"
#include "parser.h"
#include "token.h"
#include <fstream>
#include <iostream>

int main(int argc, const char **argv) {
  Lexer lexer(std::cin);
  Parser parser(lexer);

  parser.parsePrimary();

  // Token token = lexer.getToken();
  //
  // while (token.getType() != Token::Type::EndOfFile) {
  //   std::cout << "Token type: " << token.toString() << std::endl;
  //   token = lexer.getToken();
  // } 

  return 0;
}
