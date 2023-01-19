#pragma once
#include "types.h"

enum class Operator { 
  ASSIGN, 
  EQ, BANG,    
  GTR, GTQ,
  LESS, LTQ,
  NEQ,
  ADD, SUB,
  MUL, DIV, DIV_FLR, 
  POW,
  OR, AND,
};

enum class Keyword { 
  // DEFINE, 
  // EXTERN,
  MAYBE, 
  INPUT,
  CRASH, 
  WHILE,
  PRINT,
  SET,
  IF,
  ELSE
};

enum class Atom {
  PAREN_OPEN,
  PAREN_CLOSE,
  BLOCK_OPEN,
  BLOCK_CLOSE,
  END_STATEMENT,
  COMMA
};

