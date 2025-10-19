#include "builtins.h"
#include "sexp.h"
#include <math.h>



// Helper to return an error symbol 
static SExp* make_error(const char* msg) {
    return make_symbol(msg);
}

SExp* add(SExp* a, SExp* b) {
    if (!is_number(a) || !is_number(b)) return make_error("Not-a-number");
    return make_number(a->data.number + b->data.number);
}
SExp* sub(SExp* a, SExp* b) {
    if (!is_number(a) || !is_number(b)) return make_error("Not-a-number");
    return make_number(a->data.number - b->data.number);
}
SExp* mul(SExp* a, SExp* b) {
    if (!is_number(a) || !is_number(b)) return make_error("Not-a-number");
    return make_number(a->data.number * b->data.number);
}
SExp* divide(SExp* a, SExp* b) {
    if (!is_number(a) || !is_number(b)) return make_error("Not-a-number"); 
    if (b->data.number == 0) return make_error("DivisionByZero"); 
    return make_number(a->data.number / b->data.number);
}
SExp* mod(SExp* a, SExp* b) {
    if (!is_number(a) || !is_number(b)) return make_error("Not-a-number");
    if (b->data.number == 0) return make_error("DivisionByZero");
    return make_number(fmod(a->data.number, b->data.number));
}
SExp* lt(SExp* a, SExp* b) {
    if (!is_number(a) || !is_number(b)) return make_error("Not-a-number");
    return a->data.number < b->data.number ? T : NIL;
}
SExp* gt(SExp* a, SExp* b) {
    if (!is_number(a) || !is_number(b)) return make_error("Not-a-number");
    return a->data.number > b->data.number ? T : NIL;
}
SExp* lte(SExp* a, SExp* b) {
    if (!is_number(a) || !is_number(b)) return make_error("Not-a-number");
    return a->data.number <= b->data.number ? T : NIL;
}
SExp* gte(SExp* a, SExp* b) {
    if (!is_number(a) || !is_number(b)) return make_error("Not-a-number");
    return a->data.number >= b->data.number ? T : NIL;
}

SExp* eq(SExp* a, SExp* b) {
    if (a->type != b->type) return NIL; // Must be same type
    if (!is_atom(a)) return NIL;        // Must be atoms
    switch (a->type) {
        case SEXP_NIL:    return T;
        case SEXP_NUMBER: return a->data.number == b->data.number ? T : NIL;
        case SEXP_SYMBOL:
        case SEXP_STRING: return strcmp(a->data.text, b->data.text) == 0 ? T : NIL;
        default: return NIL;
    }
}

SExp* not_op(SExp* s) {
    return is_nil(s) ? T : NIL;
}

SExp* is_cons_op(SExp* arg) {
    return is_cons(arg) ? T : NIL;
}