#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "sexp.h"

// Define the global constants
SExp* NIL = NULL;
SExp* T = NULL;

void initialize_globals() {
    NIL = (SExp*)malloc(sizeof(SExp));
    NIL->type = SEXP_NIL;
    T = (SExp*)malloc(sizeof(SExp));
    T->type = SEXP_SYMBOL;
    T->data.text = (char*)malloc(strlen("T") + 1);
    strcpy(T->data.text, "T");
}

SExp* cons(SExp* car_sexp, SExp* cdr_sexp) {
    SExp* s = (SExp*)malloc(sizeof(SExp));
    s->type = SEXP_CONS;
    s->data.cons.car = car_sexp;
    s->data.cons.cdr = cdr_sexp;
    return s;
}

SExp* car(SExp* s) {
    if (!is_list(s) || is_nil(s)) {
        fprintf(stdout, "Error: 'car' called on non-list.\n");
        return NIL;
    }
    return s->data.cons.car;
}

SExp* cdr(SExp* s) {
    if (!is_list(s) || is_nil(s)) {
        fprintf(stdout, "Error: 'cdr' called on non-list.\n");
        return NIL;
    }
    return s->data.cons.cdr;
}

// cadr(s) is equivalent to car(cdr(s)) 
SExp* cadr(SExp* s) {
    return car(cdr(s));
}

// caddr(s) is equivalent to car(cdr(cdr(s))) 
SExp* caddr(SExp* s) {
    return car(cdr(cdr(s)));
}
SExp* cadddr(SExp* s) {
    return car(cdr(cdr(cdr(s))));
}

SExp* make_number(double value) {
    SExp* s = (SExp*)malloc(sizeof(SExp));
    s->type = SEXP_NUMBER;
    s->data.number = value;
    return s;
}

SExp* make_symbol(const char* text) {
    if (strcmp(text, "nil") == 0 || strcmp(text, "()") == 0) return NIL;
    SExp* s = (SExp*)malloc(sizeof(SExp));
    s->type = SEXP_SYMBOL;
    s->data.text = (char*)malloc(strlen(text) + 1);
    strcpy(s->data.text, text);
    return s;
}

SExp* make_string(const char* text) {
    SExp* s = (SExp*)malloc(sizeof(SExp));
    s->type = SEXP_STRING;
    s->data.text = (char*)malloc(strlen(text) + 1);
    strcpy(s->data.text, text);
    return s;
}

// Predicate implementations
int is_nil(SExp* s) { return s == NIL; }
int is_symbol(SExp* s) { return s->type == SEXP_SYMBOL; }
int is_number(SExp* s) { return s->type == SEXP_NUMBER; }
int is_string(SExp* s) { return s->type == SEXP_STRING; }
int is_list(SExp* s) { return s->type == SEXP_CONS || is_nil(s); }
int is_atom(SExp* s) { return !is_list(s); }
int is_cons(SExp* s) { return s->type == SEXP_CONS; }
int is_lambda(SExp* s) { return s->type == SEXP_LAMBDA; }

