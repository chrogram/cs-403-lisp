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
    SExp* symbols = NIL;
    SExp* values = NIL;
    SExp* frame = cons(symbols, values);
    // The global environment is a list containing one frame
    return cons(frame, NIL);
}

SExp* set(SExp* symbol, SExp* value, SExp* env) {
    // Adds a binding to the most local frame in the environment
    SExp* frame = car(env);
    SExp* symbols = car(frame);
    SExp* values = cdr(frame);

    frame->data.cons.car = cons(symbol, symbols);
    frame->data.cons.cdr = cons(value, values);

    return value;
}

SExp* lookup(SExp* symbol, SExp* env) {
    SExp* current_env = env;
    // Iterate through the list of environment frames (from local to global)
    while (!is_nil(current_env)) {
        SExp* frame = car(current_env);
        SExp* symbols = car(frame);
        SExp* values = cdr(frame);
        // Traverse the symbol and value lists in the current frame
        while (!is_nil(symbols)) {
            if (strcmp(car(symbols)->data.text, symbol->data.text) == 0) {
                return car(values); // Found, return corresponding value
            }
            symbols = cdr(symbols);
            values = cdr(values);
        }
        current_env = cdr(current_env); // Move to the parent environment
    }
    // If not found in any environment, return the symbol itself
    return symbol;
}

// --- Main Eval Function ---

SExp* eval(SExp* sexp, SExp* env) {
    if (sexp == NULL) return NIL;

    switch (sexp->type) {
        case SEXP_NIL:
        case SEXP_NUMBER:
        case SEXP_STRING:
        case SEXP_LAMBDA:
            return sexp;
        case SEXP_SYMBOL:
            return lookup(sexp, env);
        case SEXP_CONS:
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

    if (!is_symbol(fn_sym)) {
        SExp* lambda_obj = eval(fn_sym, env);
        if (is_lambda(lambda_obj)) {
            SExp* evaluated_args = eval_args(args, env);
            return apply(lambda_obj, evaluated_args);
        }
        return make_symbol("Error: Not a function");
    }

    // --- Special Forms ---
    if (strcmp(fn_sym->data.text, "quote") == 0) return cadr(list);
    
    if (strcmp(fn_sym->data.text, "set") == 0) return set(cadr(list), eval(caddr(list), env), env);

    if (strcmp(fn_sym->data.text, "let") == 0) return set(cadr(list), eval(caddr(list), env), env);
    
    if (strcmp(fn_sym->data.text, "if") == 0) {
        SExp* test_res = eval(cadr(list), env);
        return !is_nil(test_res) ? eval(caddr(list), env) : eval(cadddr(list), env);
    }
    
    if (strcmp(fn_sym->data.text, "and") == 0) {
        SExp* res1 = eval(cadr(list), env);
        if (is_nil(res1)) return NIL;
        return eval(caddr(list), env);
    }

    if (strcmp(fn_sym->data.text, "or") == 0) {
        SExp* res1 = eval(cadr(list), env);
        if (!is_nil(res1)) return T;
        return eval(caddr(list), env);
    }

    if (strcmp(fn_sym->data.text, "begin") == 0) {
        SExp* expressions = args;
        SExp* result = NIL;
        while (!is_nil(expressions)) {
            result = eval(car(expressions), env);
            expressions = cdr(expressions);
        }
        return result; // Return the result of the last expression
    }

    if (strcmp(fn_sym->data.text, "define") == 0) {
        SExp* name = cadr(list);
        SExp* value_or_params = caddr(list);

        // Function definition: (define name (params...) ...body)
        if (is_list(value_or_params)) {
            SExp* params = value_or_params;
            SExp* body_expressions = cdr(cdr(cdr(list))); // Replaced cdddr
            SExp* body = NIL;

            if (is_nil(cdr(body_expressions))) {
                body = car(body_expressions); // Single body expression
            } else {
                body = cons(make_symbol("begin"), body_expressions); // Implicit begin
            }
            
            SExp* lambda = (SExp*) malloc(sizeof(SExp));
            lambda->type = SEXP_LAMBDA;
            lambda->data.lambda.params = params;
            lambda->data.lambda.body = body;
            lambda->data.lambda.env = env; // Capture lexical scope

            return set(name, lambda, env);

        } else { // Variable definition: (define name value)
            return set(name, eval(value_or_params, env), env);
        }
    }
    
    if (strcmp(fn_sym->data.text, "lambda") == 0) {
        SExp* lambda = (SExp*) malloc(sizeof(SExp));
        lambda->type = SEXP_LAMBDA;
        lambda->data.lambda.params = cadr(list);
        lambda->data.lambda.body = caddr(list);
        lambda->data.lambda.env = env; // Capture the current environment
        return lambda;
    }

    // --- Regular Function Call ---
    SExp* fn_obj = eval(fn_sym, env);
    SExp* evaluated_args = eval_args(args, env);
    return apply(fn_obj, evaluated_args);
}

// --- Apply Function ---

static SExp* apply(SExp* fn_sexp, SExp* args) {
    // Handle user-defined lambda functions
    if (is_lambda(fn_sexp)) {
        // Create a new local frame for arguments
        SExp* local_frame = cons(NIL, NIL);
        SExp* formal_params = fn_sexp->data.lambda.params;
        SExp* actual_args = args;

        while(!is_nil(formal_params)) {
            // Add bindings to the new local frame
            local_frame->data.cons.car = cons(car(formal_params), car(local_frame));
            local_frame->data.cons.cdr = cons(car(actual_args), cdr(local_frame));
            formal_params = cdr(formal_params);
            actual_args = cdr(actual_args);
        }

        // CORRECTED: Create a new environment by linking the local frame to the function's closure environment
        SExp* call_env = cons(local_frame, fn_sexp->data.lambda.env);
        
        // Evaluate the function body in this new, extended environment
        return eval(fn_sexp->data.lambda.body, call_env);
    }

    // Handle Built-in functions
    if (!is_symbol(fn_sexp)) return make_symbol("ApplyError: Not a function symbol");
    
    const char* op = fn_sexp->data.text;
    SExp* arg1 = car(args);
    SExp* arg2 = cdr(args) != NIL ? car(cdr(args)) : NIL;

    if (strcmp(op, "car") == 0) return car(arg1);
    if (strcmp(op, "cdr") == 0) return cdr(arg1);
    if (strcmp(op, "cons") == 0) return cons(arg1, arg2);

    // Predicates
    if (strcmp(op, "isSymbol") == 0) return is_symbol(arg1) ? T : NIL;
    if (strcmp(op, "isNumber") == 0) return is_number(arg1) ? T : NIL;
    if (strcmp(op, "isString") == 0) return is_string(arg1) ? T : NIL;
    if (strcmp(op, "isList") == 0) return (is_cons(arg1) || is_nil(arg1)) ? T : NIL;
    if (strcmp(op, "isNil") == 0) return is_nil(arg1) ? T : NIL;
    if (strcmp(op, "isCons") == 0) return is_cons_op(arg1);

    // Arithmetic
    if (strcmp(op, "add") == 0 || strcmp(op, "+") == 0) return add(arg1, arg2);
    if (strcmp(op, "sub") == 0 || strcmp(op, "-") == 0) return sub(arg1, arg2);
    if (strcmp(op, "mul") == 0 || strcmp(op, "*") == 0) return mul(arg1, arg2);
    if (strcmp(op, "div") == 0 || strcmp(op, "/") == 0) return divide(arg1, arg2);
    if (strcmp(op, "mod") == 0) return mod(arg1, arg2);

    // Relational/Logical
    if (strcmp(op, "eq") == 0) return eq(arg1, arg2);
    if (strcmp(op, "gt") == 0) return gt(arg1, arg2);
    if (strcmp(op, "gte") == 0) return gte(arg1, arg2);
    if (strcmp(op, "lt") == 0) return lt(arg1, arg2);
    if (strcmp(op, "lte") == 0) return lte(arg1, arg2);
    if (strcmp(op, "not") == 0) return not_op(arg1);

    return make_symbol("ApplyError: Unknown built-in function");
}