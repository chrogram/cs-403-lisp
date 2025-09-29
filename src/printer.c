#include "sexp.h"
#include "printer.h"
#include <stdio.h>

static void print_list(SExp* s) {
    print_sexp(s->data.cons.car);
    SExp* current_cdr = s->data.cons.cdr;

    if (is_nil(current_cdr)) return;
    if (is_list(current_cdr)) {
        printf(" ");
        print_list(current_cdr);
    } else {
        printf(" . ");
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
        case SEXP_LAMBDA: printf("#<function>"); break; // New case
        case SEXP_CONS:
            printf("(");
            print_list(s);
            printf(")");
            break;
    }
}