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
  DEFINE, 
  EXTERN,
  PRINT,
  SET
};

enum class Atom {
  PAREN_OPEN,
  PAREN_CLOSE,
  COMMA,
  END_STATEMENT
};
