#include <stdio.h>
#include <string.h>
#include "sexp.h"
#include "builtins.h"

int main(int argc, char* argv[]) {

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <mode>\n", argv[0]);
        printf("Modes: R - REPL\n");
        printf("       T - Tester\n");
        return 1;
    }

    char mode = argv[1][0];


    initialize_globals(); // Initialize global constants NIL and T

    if (mode == 'T') {
        printf("--- Sprint 1: Reading and Printing S-Expressions ---\n");
        SExp* list1 = sexp("(a b c)");
        printf("Parsed== '(a b c)': ");
        print_sexp(list1);
        printf("\n");

        SExp* nested_list = sexp("((a (789) x) (b (456) y))");
        printf("Parsed== '((a (789) x) (b (456) y))': ");
        print_sexp(nested_list);
        printf("\n");

        SExp* dotted_pair = cons(make_symbol("a"), make_symbol("b"));
        printf("Printing a dotted pair== '(a . b)': ");
        print_sexp(dotted_pair);
        printf("\n\n");

        printf("--- Sprint 2: Predicates, Constructors, and Accessors ---\n");
        SExp* num = sexp("123");
        SExp* lst = sexp("(1 2)");

        printf("Is '123' a number? %s\n", is_number(num) ? "Yes" : "No");
        printf("Is '(1 2)' a list? %s\n", is_list(lst) ? "Yes" : "No");
        
        printf("car of (1 2) is: ");
        print_sexp(car(lst));
        printf("\n");

        printf("cdr of (1 2) is: ");
        print_sexp(cdr(lst));
        printf("\n\n");
        
        printf("--- Sprint 3: Core Arithmetic and Logic ---\n");
        SExp* num1 = make_number(10);
        SExp* num2 = make_number(5);
        SExp* sym1 = make_symbol("foo");

        printf("add(10, 5) -> "); print_sexp(add(num1, num2)); printf("\n");
        printf("div(10, 0) -> "); print_sexp(divide(num1, make_number(0))); printf("\n");
        printf("gt(10, 5)  -> "); print_sexp(gt(num1, num2)); printf("\n");
        printf("eq(foo, foo)-> "); print_sexp(eq(sym1, make_symbol("foo"))); printf("\n");
        printf("not(nil)   -> "); print_sexp(not_op(NIL)); printf("\n");
    }
    else if (mode == 'R') {
        char input_buffer[2048];
        printf("Welcome to C-Sexp REPL. Type 'quit' to exit.\n");

        while (1) {
            printf("> ");
            if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
                printf("\nExiting REPL.\n");
                break; // Exit on EOF (Ctrl+D)
            }

            // Remove trailing newline from fgets
            input_buffer[strcspn(input_buffer, "\n")] = 0;

            if (strcmp(input_buffer, "quit") == 0) {
                printf("Exiting REPL.\n");
                break;
            }

            if (strlen(input_buffer) > 0) {
                SExp* expression = sexp(input_buffer);
                if (expression) {
                    print_sexp(expression);
                    printf("\n");
                    
                } else {
                    fprintf(stderr, "Error: Could not parse expression.\n");
                }
            }
        }
    } 
    else {
        fprintf(stderr, "Invalid mode. Use 'R' for REPL or 'T' for Tester.\n");
        return 1;
    }

    return 0;
}