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
        
        printf("Parsing Symbol\n");
        SExp* symbol1 = sexp("a");
        printf("Parsed== 'a':: \n");
        print_sexp(symbol1);
        printf("\n");

        printf("\nParsing String\n");
        SExp* string1 = sexp("\"hello\"");
        printf("Parsed== '\"hello\"':: \n");
        print_sexp(string1);
        printf("\n");

        printf("\nParsing Number\n");
        SExp* number1 = sexp("123");
        printf("Parsed== '123':: \n");
        print_sexp(number1);
        printf("\n");
        
        printf("\nParsing List\n");
        SExp* list1 = sexp("(a b c)");
        printf("Parsed== '(a b c)':: \n");
        print_sexp(list1);
        printf("\n");
        
        printf("\nUnclosed Parenthesis Test\n");
        SExp* list2 = sexp("(a b c ");
        printf("Parsed== '(a b c ':: \n");
        print_sexp(list2);
        printf("\n");

        printf("\nParsing Nested List\n");
        SExp* nested_list = sexp("((a (789) x) (b (456) y))");
        printf("Parsed== '((a (789) x) (b (456) y))':: \n");
        print_sexp(nested_list);
        printf("\n");

        printf("\nParsing Dotted Pair\n");
        SExp* dotted_pair = sexp("(a . (b . (c . d)))");
        printf("Parsed== '(a . (b . (c . d)))':: \n");
        print_sexp(dotted_pair);
        printf("\n");



        printf("\n--- Sprint 2: Predicates, Constructors, and Accessors ---\n\n");
        SExp* symbol = make_symbol("a");
        SExp* num = sexp("123");
        SExp* list = sexp("(1 2)");
        SExp* string = make_string("foo_bar");
        
        // Symbol Test Cases
        printf("is_symbol Test Cases:\n");
        printf("Is 'a' a symbol? %s\n", is_symbol(symbol) ? "Yes" : "No");
        printf("Is (1 2) a symbol? %s\n", is_symbol(list) ? "Yes" : "No");
        printf("\n");

        // Number Test Cases
        printf("is_number Test Cases:\n");
        printf("Is '123' a number? %s\n", is_number(num) ? "Yes" : "No");
        printf("Is 'a' a number? %s\n", is_number(symbol) ? "Yes" : "No");
        printf("\n");

        // String Test Cases
        printf("is_string Test Cases:\n");
        printf("Is \"foo_bar\" a string? %s\n", is_string(string) ? "Yes" : "No");
        printf("Is 'a' a string? %s\n", is_string(symbol) ? "Yes" : "No");
        printf("\n");

        // List Test Cases
        printf("is_list Test Cases:\n");
        printf("Is '(1 2)' a list? %s\n", is_list(list) ? "Yes" : "No");
        printf("Is '123' a list? %s\n", is_list(num) ? "Yes" : "No");
        printf("\n");

        // Nil Test Cases
        printf("is_nil Test Cases:\n");
        printf("Is T a nil? %s\n", is_nil(T) ? "Yes" : "No");
        printf("Is nil a nil? %s\n", is_nil(NIL) ? "Yes" : "No");
        printf("\n");
        
        printf("car/cdr Test Cases:\n");
        printf("car of (1 2) is: ");
        print_sexp(car(list));
        printf("\n");
        printf("car of '123' is: ");
        print_sexp(car(num));
        printf("\n\n");

        printf("cdr of (1 2) is: ");
        print_sexp(cdr(list));
        printf("\n");
        printf("cdr of (1 2 3) is: ");
        print_sexp(cdr(sexp("(1 2 3)")));
        printf("\n");
        printf("cdr of (1) is: ");
        print_sexp(cdr(sexp("(1)")));
        printf("\n");
        printf("cdr of '123' is: ");
        print_sexp(cdr(num));
        printf("\n");
        
        printf("\n--- Sprint 3: Core Arithmetic and Logic ---\n");
        SExp* num1 = make_number(5);
        SExp* num2 = make_number(10);
        SExp* num3 = make_number(1.5);
        SExp* num4 = make_number(2.25);
        SExp* sym1 = make_symbol("foo");

        printf("\nadd() Test Cases:\n");
        printf("add(5, 10) -> \t"); print_sexp(add(num1, num2)); printf("\n");
        printf("add(1.5, 2.25) -> \t"); print_sexp(add(num3, num4)); printf("\n");

        printf("\nsub() Test Cases:\n");
        printf("sub(10, 5) -> \t"); print_sexp(sub(num2, num1)); printf("\n");
        printf("sub(5, 10) -> \t"); print_sexp(sub(num1, num2)); printf("\n");

        printf("\nmultiply() Test Cases:\n");
        printf("mul(5, 10) -> \t"); print_sexp(mul(num1, num2)); printf("\n");
        printf("mul(0, 10) -> \t"); print_sexp(mul(make_number(0), num2)); printf("\n");
        printf("mul(5, 1.5) -> \t"); print_sexp(mul(num1, make_number(1.5))); printf("\n");

        printf("\ndivide() Test Cases:\n");
        printf("div(10, 5) -> \t"); print_sexp(divide(num2, num1)); printf("\n");
        printf("div(2.25, 3) -> \t"); print_sexp(divide(num4, make_number(3))); printf("\n");
        printf("div(0, 5) -> \t"); print_sexp(divide(make_number(0), num1)); printf("\n");
        printf("div(5, 0) -> \t"); print_sexp(divide(num1, make_number(0))); printf("\n");

        printf("\nmod() Test Cases:\n");
        printf("mod(10, 3) -> \t"); print_sexp(mod(num2, make_number(3))); printf("\n");
        printf("mod(10, 0) -> \t"); print_sexp(mod(num2, make_number(0))); printf("\n");

        printf("\nRelational Function Test Cases:\n");
        printf("gt(5, 10)  -> \t"); print_sexp(gt(num1, num2)); printf("\n");
        printf("gt(10, 5)  -> \t"); print_sexp(gt(num2, num1)); printf("\n");
        printf("gt(5, 5)  -> \t"); print_sexp(gt(num1, num1)); printf("\n");
        printf("gt(a, 5) -> \t"); print_sexp(gt(sym1, num1)); printf("\n");
        printf("gt(5, a) -> \t"); print_sexp(gt(sym1, num1)); printf("\n");
        printf("gte(10, 5) -> \t"); print_sexp(gte(num1, num2)); printf("\n");
        printf("gte(10, 10) -> \t"); print_sexp(gte(num1, num1)); printf("\n");
        printf("lt(10, 5)  -> \t"); print_sexp(lt(num1, num2)); printf("\n");
        printf("lte(5, 10) -> \t"); print_sexp(lte(num1, num2)); printf("\n");
        printf("eq(foo, foo)-> \t"); print_sexp(eq(sym1, make_symbol("foo"))); printf("\n");
        printf("eq(foo, bar)-> \t"); print_sexp(eq(sym1, make_symbol("bar"))); printf("\n");
        printf("eq(foo, 1)-> \t"); print_sexp(eq(sym1, make_number(5))); printf("\n");
        printf("not(nil)   -> \t"); print_sexp(not_op(NIL)); printf("\n");
        printf("not(T)   -> \t"); print_sexp(not_op(T)); printf("\n");

        printf("\nArithmetic on Non-Numbers Test Cases:\n");
        printf("add(5, foo) -> \t"); print_sexp(add(num1, sym1)); printf("\n");
        printf("sub(foo, 5) -> \t"); print_sexp(sub(sym1, num1)); printf("\n");

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
                    fprintf(stdout, "Error: Could not parse expression.\n");
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