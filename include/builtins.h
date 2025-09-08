#ifndef BUILTINS_H
#define BUILTINS_H

#include "sexp.h"
#include <math.h>
#include <string.h>

// Sprint 3: Number Functions
SExp* add(SExp* a, SExp* b); 
SExp* sub(SExp* a, SExp* b); 
SExp* mul(SExp* a, SExp* b); 
SExp* divide(SExp* a, SExp* b);
SExp* mod(SExp* a, SExp* b); 

// Sprint 3: Relational Functions
SExp* lt(SExp* a, SExp* b);  
SExp* gt(SExp* a, SExp* b);  
SExp* lte(SExp* a, SExp* b); 
SExp* gte(SExp* a, SExp* b); 

// Sprint 3: Equality and Logical Functions 
SExp* eq(SExp* a, SExp* b);
SExp* not_op(SExp* s); 

#endif 