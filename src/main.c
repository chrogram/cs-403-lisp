#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "builtins.h"
#include "eval.h"
#include "parser.h"
#include "printer.h"
#include "sexp.h"


int main() {
    initialize_globals();
    SExp* global_env = create_global_env();

    // Pre-load built-in function names into the environment
    set(make_symbol("car"), make_symbol("car"), global_env);
    set(make_symbol("cdr"), make_symbol("cdr"), global_env);
    set(make_symbol("cons"), make_symbol("cons"), global_env);
    set(make_symbol("add"), make_symbol("add"), global_env);
    set(make_symbol("+"), make_symbol("+"), global_env);
    set(make_symbol("sub"), make_symbol("sub"), global_env);
    set(make_symbol("-"), make_symbol("-"), global_env);
    set(make_symbol("mul"), make_symbol("mul"), global_env);
    set(make_symbol("*"), make_symbol("*"), global_env);
    set(make_symbol("div"), make_symbol("div"), global_env);
    set(make_symbol("/"), make_symbol("/"), global_env);
    set(make_symbol("mod"), make_symbol("mod"), global_env);
    set(make_symbol("eq"), make_symbol("eq"), global_env);
    set(make_symbol("gt"), make_symbol("gt"), global_env);
    set(make_symbol("lt"), make_symbol("lt"), global_env);
    set(make_symbol("not"), make_symbol("not"), global_env);

    printf("Welcome to the Lisp Interpreter!\n");
    printf("Enter an expression, or type \"quit\" to exit.\n");

    char input_buffer[2048];

    // The Read-Eval-Print Loop 
    while (1) {
        printf("> ");
        fflush(stdout);

        if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
            printf("\nExiting.\n");
            break;
        }

        input_buffer[strcspn(input_buffer, "\n")] = 0;
        if (strcmp(input_buffer, "quit") == 0) break;
        if (strlen(input_buffer) == 0) continue;

        // 1. READ
        SExp* parsed_expr = sexp(input_buffer);
        if (!parsed_expr) {
            // Error messages are printed by the parser
            continue;
        }

        // 2. EVAL
        SExp* result = eval(parsed_expr, global_env);

        // 3. PRINT
        print_sexp(result);
        printf("\n");
    }

    printf("Goodbye!\n");
    return 0;
}