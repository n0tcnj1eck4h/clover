#include "ast/stmt/crashStmtAST.h"
#include <cstdlib>

void CrashStmtAST::execute(Environment &env) {
  abort();
}
