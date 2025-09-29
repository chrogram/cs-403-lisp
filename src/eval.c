#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "eval.h"
#include "builtins.h"

// Forward declarations
static SExp* eval_list(SExp* list, SExp* env);
static SExp* apply(SExp* fn_sexp, SExp* args);

// --- Environment Management ---

SExp* create_global_env() {
    // Environment is a list of two lists: ( (symbols...) (values...) ) [cite: 22]
    SExp* symbols = NIL;
    SExp* values = NIL;
    return cons(symbols, values);
}

SExp* set(SExp* symbol, SExp* value, SExp* env) {
    SExp* symbols = car(env);
    SExp* values = cdr(env);
    // Add new symbol-value pair to the front of the lists [cite: 28]
    car(env)->data.cons.car = cons(symbol, symbols)->data.cons.car;
    cdr(env)->data.cons.car = cons(value, values)->data.cons.car;
    return value; // Return the evaluated value [cite: 56]
}

SExp* lookup(SExp* symbol, SExp* env) {
    SExp* parent_env = env;
    while (!is_nil(parent_env)) {
        SExp* symbols = car(parent_env);
        SExp* values = cdr(parent_env);
        // Traverse the symbol and value lists in parallel [cite: 35]
        while (!is_nil(symbols)) {
            if (strcmp(car(symbols)->data.text, symbol->data.text) == 0) {
                return car(values); // Found, return corresponding value
            }
            symbols = cdr(symbols);
            values = cdr(values);
        }
        // This is for local environments; not implemented until Sprint 7
        // For now, it will just check the global env once.
        break; 
    }
    // If not found, return the symbol itself [cite: 39]
    return symbol; 
}


// --- Main Eval Function ---

SExp* eval(SExp* sexp, SExp* env) {
    if (sexp == NULL) return NIL;

    switch (sexp->type) {
        // Atoms evaluate to themselves [cite: 15]
        case SEXP_NIL:
        case SEXP_NUMBER:
        case SEXP_STRING:
        case SEXP_LAMBDA: // Lambdas are values
            return sexp;

        case SEXP_SYMBOL:
            // Symbols are looked up in the environment [cite: 13]
            return lookup(sexp, env);

        case SEXP_CONS:
            // Lists are function calls or special forms [cite: 16]
            return eval_list(sexp, env);
    }
    return make_symbol("EvalError: UnknownType");
}


// --- List Evaluation ---

static SExp* eval_args(SExp* args, SExp* env) {
    if (is_nil(args)) return NIL;
    SExp* evaluated_car = eval(car(args), env);
    SExp* evaluated_cdr = eval_args(cdr(args), env);
    return cons(evaluated_car, evaluated_cdr);
}

static SExp* eval_list(SExp* list, SExp* env) {
    SExp* fn_sym = car(list);
    SExp* args = cdr(list);

    if (!is_symbol(fn_sym)) { // Handle calls like ((lambda (x) x) 5)
        SExp* lambda_obj = eval(fn_sym, env);
        if (is_lambda(lambda_obj)) {
            SExp* evaluated_args = eval_args(args, env);
            return apply(lambda_obj, evaluated_args);
        }
        return make_symbol("Error: Not a function");
    }

    // --- Special Forms (arguments are not pre-evaluated) ---
    
    // (quote x) -> x [cite: 51]
    if (strcmp(fn_sym->data.text, "quote") == 0) {
        return cadr(list);
    }

    // (set sym val) [cite: 52]
    if (strcmp(fn_sym->data.text, "set") == 0) {
        SExp* value = eval(caddr(list), env); // Value is evaluated [cite: 53]
        return set(cadr(list), value, env);
    }

    // (if test then else) [cite: 130]
    if (strcmp(fn_sym->data.text, "if") == 0) {
        SExp* test_res = eval(cadr(list), env);
        if (!is_nil(test_res)) {
            return eval(caddr(list), env); // Eval 'then' branch [cite: 132]
        } else {
            return eval(car(cdr(cdr(list))), env); // Eval 'else' branch [cite: 133]
        }
    }
    
    // (define name params body) [cite: 182]
    if (strcmp(fn_sym->data.text, "define") == 0) {
        SExp* lambda = (SExp*) malloc(sizeof(SExp));
        lambda->type = SEXP_LAMBDA;
        lambda->data.lambda.params = caddr(list);
        lambda->data.lambda.body = car(cdr(cdr(cdr(list))));
        lambda->data.lambda.env = env; // Lexical scoping
        return set(cadr(list), lambda, env);
    }

    // (lambda params body) [cite: 280]
    if (strcmp(fn_sym->data.text, "lambda") == 0) {
        SExp* lambda = (SExp*) malloc(sizeof(SExp));
        lambda->type = SEXP_LAMBDA;
        lambda->data.lambda.params = cadr(list);
        lambda->data.lambda.body = caddr(list);
        lambda->data.lambda.env = env;
        return lambda;
    }

    // --- Regular Function Call (arguments are pre-evaluated) ---

    // Evaluate the function symbol itself to see if it's a lambda [cite: 206]
    SExp* fn_obj = eval(fn_sym, env);
    // Evaluate all arguments before calling the function [cite: 62]
    SExp* evaluated_args = eval_args(args, env);
    
    return apply(fn_obj, evaluated_args);
}


// --- Apply Function ---

static SExp* apply(SExp* fn_sexp, SExp* args) {
    if (is_lambda(fn_sexp)) {
        // This is a simplified environment handling for demonstration.
        // A full implementation would chain environments.
        SExp* local_env = create_global_env(); 
        
        SExp* formal_params = fn_sexp->data.lambda.params;
        SExp* actual_args = args;
        
        // Bind arguments to parameters in the new local environment [cite: 212]
        while(!is_nil(formal_params)) {
            set(car(formal_params), car(actual_args), local_env);
            formal_params = cdr(formal_params);
            actual_args = cdr(actual_args);
        }
        
        // Evaluate the function body in the new environment [cite: 214]
        return eval(fn_sexp->data.lambda.body, local_env);
    }

    // Handle Built-in functions
    const char* op = fn_sexp->data.text;
    SExp* arg1 = car(args);
    SExp* arg2 = cdr(args) != NIL ? car(cdr(args)) : NIL;

    if (strcmp(op, "car") == 0) return car(arg1);
    if (strcmp(op, "cdr") == 0) return cdr(arg1);
    if (strcmp(op, "cons") == 0) return cons(arg1, arg2);
    if (strcmp(op, "add") == 0 || strcmp(op, "+") == 0) return add(arg1, arg2);
    if (strcmp(op, "sub") == 0 || strcmp(op, "-") == 0) return sub(arg1, arg2);
    if (strcmp(op, "mul") == 0 || strcmp(op, "*") == 0) return mul(arg1, arg2);
    if (strcmp(op, "div") == 0 || strcmp(op, "/") == 0) return divide(arg1, arg2);
    if (strcmp(op, "mod") == 0) return mod(arg1, arg2);
    if (strcmp(op, "eq") == 0) return eq(arg1, arg2);
    if (strcmp(op, "gt") == 0) return gt(arg1, arg2);
    if (strcmp(op, "lt") == 0) return lt(arg1, arg2);
    if (strcmp(op, "not") == 0) return not_op(arg1);
    
    return make_symbol("ApplyError: Not a function");
}