#ifndef SEXP_H
#define SEXP_H

// An enum to differentiate between S-Expression types
typedef enum {
    SEXP_NIL,
    SEXP_CONS,
    SEXP_SYMBOL,
    SEXP_NUMBER,
    SEXP_STRING
} SExpType;

// The primary S-Expression structure, using a tagged union.
typedef struct SExp {
    SExpType type;
    union {
        // For SEXP_CONS
        struct {
            struct SExp* car;
            struct SExp* cdr;
        } cons;
        // For SEXP_NUMBER
        double number;
        // For SEXP_SYMBOL and SEXP_STRING
        char* text;
    } data;
} SExp;

// Global constants for nil (false) and T (true)
extern SExp* NIL;
extern SExp* T;

// --- Function Prototypes ---

// Initialization
void initialize_globals();

// Printer for printer.c
void print_sexp(SExp* s);

// Parser for parser.c
SExp* sexp(const char* input_str);

// Sprint 1 & 2: Constructors and Accessors
SExp* cons(SExp* car_sexp, SExp* cdr_sexp);
SExp* car(SExp* s);
SExp* cdr(SExp* s);

// Factory functions for creating atoms
SExp* make_number(double value);
SExp* make_symbol(const char* text);
SExp* make_string(const char* text);

// Sprint 2: Predicates / Type Checkers
int is_nil(SExp* s);
int is_symbol(SExp* s);
int is_number(SExp* s);
int is_string(SExp* s);
int is_list(SExp* s);
int is_atom(SExp* s); // Helper for Sprint 3
int sexp_to_bool(SExp* s);

#endif // SEXP_H