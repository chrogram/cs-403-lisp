#ifndef EVAL_H
#define EVAL_H

#include "sexp.h"

// The main evaluation function
SExp* eval(SExp* sexp, SExp* env);

// Environment Management
SExp* create_global_env();
SExp* set(SExp* symbol, SExp* value, SExp* env);
SExp* lookup(SExp* symbol, SExp* env);

#endif // EVAL_H