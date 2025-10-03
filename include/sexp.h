#ifndef SEXP_H
#define SEXP_H

// An enum to differentiate between S-Expression types
typedef enum {
    SEXP_NIL,
    SEXP_CONS,
    SEXP_SYMBOL,
    SEXP_NUMBER,
    SEXP_STRING,
    SEXP_LAMBDA // New type for user-defined functions
} SExpType;

// Forward declaration
typedef struct SExp SExp;

// The primary S-Expression structure, using a tagged union.
struct SExp {
    SExpType type;
    union {
        // For SEXP_CONS
        struct {
            SExp* car;
            SExp* cdr;
        } cons;
        // For SEXP_NUMBER
        double number;
        // For SEXP_SYMBOL and SEXP_STRING
        char* text;
        // For SEXP_LAMBDA
        struct {
            SExp* params;
            SExp* body;
            SExp* env; // The environment where the lambda was defined
        } lambda;
    } data;
};

// Global constants for nil (false) and T (true)
extern SExp* NIL;
extern SExp* T;

// --- Function Prototypes ---

// Initialization
void initialize_globals();

// Sprint 1 & 2: Constructors and Accessors
SExp* cons(SExp* car_sexp, SExp* cdr_sexp);
SExp* car(SExp* s);
SExp* cdr(SExp* s);

// Helper accessors for list elements 
SExp* cadr(SExp* s);
SExp* caddr(SExp* s);
SExp* cadddr(SExp* s);
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
int is_atom(SExp* s);
int is_lambda(SExp* s);

#endif // SEXP_H