#ifndef BUILTINS_H
#define BUILTINS_H

#include "sexp.h"
#include <math.h> // For fmod
#include <string.h>

// Sprint 3: Number Functions [cite: 5]
SExp* add(SExp* a, SExp* b); // [cite: 11]
SExp* sub(SExp* a, SExp* b); // [cite: 12]
SExp* mul(SExp* a, SExp* b); // [cite: 13]
SExp* divide(SExp* a, SExp* b); // [cite: 14]
SExp* mod(SExp* a, SExp* b); // [cite: 15]

// Sprint 3: Relational Functions
SExp* lt(SExp* a, SExp* b);  // [cite: 16]
SExp* gt(SExp* a, SExp* b);  // [cite: 17]
SExp* lte(SExp* a, SExp* b); // [cite: 18]
SExp* gte(SExp* a, SExp* b); // [cite: 19]

// Sprint 3: Equality and Logical Functions [cite: 20]
SExp* eq(SExp* a, SExp* b); // [cite: 22]
SExp* not_op(SExp* s); // [cite: 23]

#endif // BUILTINS_H