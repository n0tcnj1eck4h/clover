#include "environment.h"
#include "errors.h"
#include "lexer.h"
#include "parser.h"
#include "token.h"
#include "value.h"
#include "ANSI-color-codes.h"
#include <cstdlib>
#include <ctime>
#include <exception>
#include <sstream>
#include <string>
#include <sysexits.h>
#include <fstream>
#include <iostream>

int main(int argc, const char **argv) {
  srand(time(nullptr));

  // Assert proper usage
  if(argc > 2) {
    std::cout << "Usage: " << argv[0] << " [script]" << std::endl;
    exit(EX_USAGE);
  }

  // Read script from file if available
  if(argc == 2) {
    std::ifstream script(argv[1]);

    if(!script.good()) {
      std::cout << "Failed to open " << argv[1] << std::endl;
      exit(EX_DATAERR);
    }
    
    Lexer lexer(script);
    Parser parser(lexer);
    Environment env;
    auto statements = parser.parse();
    try {
      for(auto& s : statements)
        s->execute(env);
      }
    catch (std::exception& e) {
      std::cerr << e.what();
    }
    exit(EX_OK);
  }

  // Enter REPL mode if no arguments were passed
  std::cout << "// TODO: Insert a cool header here" << std::endl;
  Environment env;
  do {
    std::cout << "> ";  
    std::string temp;
    std::getline(std::cin, temp);
    std::stringstream ss(temp);
    try {
      Lexer lexer(ss);
      Parser parser(lexer);
      auto statements = parser.parse();
      for(auto& s : statements) {
        s->execute(env);
      }
    } catch(UnexpectedTokenException& e) {
      for(int i = 0; i < e.getToken().col; i++)
        std::cerr << ' ';
      std::cerr << RED << " ^ " << e.what() << CRESET << std::endl;
    } 
  } while (!std::cin.eof()); 
  std::cout << "\no/\n";

  // // Enter REPL mode if no arguments were passed
  // std::cout << "// TODO: Insert a cool header here" << std::endl;
  // do {
  //   std::cout << "> ";  
  //
  //   std::string temp;
  //   std::getline(std::cin, temp);
  //   std::stringstream ss(temp);
  //
  //   try {
  //     Lexer lexer(ss);
  //     Parser parser(lexer);
  //     auto expr = parser.parseExpression();
  //     std::cout << expr->evaluate().toString() << std::endl;
  //   } catch(UnexpectedTokenException& e) {
  //     if(e.getToken().getType() == Token::Type::EndOfFile) {
  //       std::cout << "\no/\n";
  //       break;
  //     }
  //     std::cerr << e.what() << std::endl;
  //   } catch(std::exception& e) {
  //     std::cerr << e.what() << std::endl;
  //   }
  // } while (true);

  // do {
  //   std::cout << "> ";  
  //   token = lexer.getToken();
  //   std::cout << "Token type: " << token.toString() << std::endl;
  // } while (token.getType() != Token::Type::EndOfFile);

  return EX_OK;
}
