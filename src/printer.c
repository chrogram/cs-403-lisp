#include "sexp.h"
#include <stdio.h>

void print_sexp(SExp* s);

static void print_list(SExp* s) {
    print_sexp(s->data.cons.car);
    SExp* current_cdr = s->data.cons.cdr;

    if (is_nil(current_cdr)) {
        return;
    } else if (is_list(current_cdr)) {
        printf(" ");
        print_list(current_cdr);
    } else {
        printf(" . "); // Dotted pair printing 
        print_sexp(current_cdr);
    }
}

void print_sexp(SExp* s) {
    if (!s) return;
    switch (s->type) {
        case SEXP_NIL:    printf("nil"); break;
        case SEXP_NUMBER: printf("%g", s->data.number); break;
        case SEXP_SYMBOL: printf("%s", s->data.text); break;
        case SEXP_STRING: printf("\"%s\"", s->data.text); break;
        case SEXP_CONS:
            printf("(");
            print_list(s);
            printf(")");
            break;
    }
}