#include "lexer.h"
#include "parser.h"
#include "token.h"
#include <cstdlib>
#include <sysexits.h>
#include <fstream>
#include <iostream>
#include "value.h"

int main(int argc, const char **argv) {
  if(argc > 2) {
    std::cout << "Usage: " << argv[0] << " [script]" << std::endl;
    exit(EX_USAGE);
  }

  if(argc == 2) {
    std::ifstream script(argv[1]);

    if(!script.good()) {
      std::cout << "Failed to open " << argv[1] << std::endl;
      exit(EX_DATAERR);
    }
    
    Lexer lexer(script);
    Parser parser(lexer);
    auto expr = parser.parsePrimary();
    std::cout << expr->evaluate().toString() << std::endl;
    exit(EX_OK);
  }

  Lexer lexer(std::cin);
  Token token;

  do {
    std::cout << "> ";  
    Parser parser(lexer);
    auto expr = parser.parsePrimary();
    std::cout << expr->evaluate().toString() << std::endl;
  } while (true);

  // do {
  //   std::cout << "> ";  
  //   token = lexer.getToken();
  //   std::cout << "Token type: " << token.toString() << std::endl;
  // } while (token.getType() != Token::Type::EndOfFile);

  return EX_OK;
}
