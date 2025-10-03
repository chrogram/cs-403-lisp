#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "builtins.h"
#include "eval.h"
#include "parser.h"
#include "printer.h"
#include "sexp.h"


int main(int argc, char* argv[]) {

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <mode>\n", argv[0]);
        printf("Modes: R - REPL\n");
        printf("       T - Tester\n");
        return 1;
    }

    char mode = argv[1][0];

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
    set(make_symbol("gte"), make_symbol("gte"), global_env);
    set(make_symbol("lt"), make_symbol("lt"), global_env);
    set(make_symbol("lte"), make_symbol("lte"), global_env);
    set(make_symbol("not"), make_symbol("not"), global_env);

    printf("Welcome to the Lisp Interpreter!\n");
    printf("Enter an expression, or type \"quit\" to exit.\n");

    char input_buffer[2048];

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
        printf("car of (1 2)     -> ");
        print_sexp(car(list));
        printf("\n");
        printf("car of '123'     -> ");
        print_sexp(car(num));
        printf("\n\n");
        printf("cdr of (1 2)     -> ");
        print_sexp(cdr(list));
        printf("\n");
        printf("cdr of (1 2 3)   -> ");
        print_sexp(cdr(sexp("(1 2 3)")));
        printf("\n");
        printf("cdr of (1)       -> ");
        print_sexp(cdr(sexp("(1)")));
        printf("\n");
        printf("cdr of '123'     -> ");
        print_sexp(cdr(num));
        printf("\n");



        printf("\n--- Sprint 3: Core Arithmetic and Logic ---\n");
        SExp* num1 = make_number(5);
        SExp* num2 = make_number(10);
        SExp* num3 = make_number(1.5);
        SExp* num4 = make_number(2.25);
        SExp* sym1 = make_symbol("foo");



        printf("\nadd() Test Cases:\n");
        printf("add(5, 10)       -> "); print_sexp(add(num1, num2)); printf("\n");
        printf("add(1.5, 2.25)   -> "); print_sexp(add(num3, num4)); printf("\n");

        printf("\nsubtract() Test Cases:\n");
        printf("sub(10, 5)       -> "); print_sexp(sub(num2, num1)); printf("\n");
        printf("sub(5, 10)       -> "); print_sexp(sub(num1, num2)); printf("\n");



        printf("\nmultiply() Test Cases:\n");
        printf("mul(5, 10)       -> "); print_sexp(mul(num1, num2)); printf("\n");
        printf("mul(0, 10)       -> "); print_sexp(mul(make_number(0), num2)); printf("\n");
        printf("mul(5, 1.5)      -> "); print_sexp(mul(num1, make_number(1.5))); printf("\n");



        printf("\ndivide() Test Cases:\n");
        printf("div(10, 5)       -> "); print_sexp(divide(num2, num1)); printf("\n");
        printf("div(2.25, 3)     -> "); print_sexp(divide(num4, make_number(3))); printf("\n");
        printf("div(0, 5)        -> "); print_sexp(divide(make_number(0), num1)); printf("\n");
        printf("div(5, 0)        -> "); print_sexp(divide(num1, make_number(0))); printf("\n");

        printf("\nmod() Test Cases:\n");
        printf("mod(10, 3)       -> "); print_sexp(mod(num2, make_number(3))); printf("\n");
        printf("mod(10, 0)       -> "); print_sexp(mod(num2, make_number(0))); printf("\n");



        printf("\nRelational Function Test Cases:\n");

        printf("gt(5, 10)        -> "); print_sexp(gt(num1, num2)); printf("\n");
        printf("gt(10, 5)        -> "); print_sexp(gt(num2, num1)); printf("\n");
        printf("gt(5, 5)         -> "); print_sexp(gt(num1, num1)); printf("\n");
        printf("gt(a, 5)         -> "); print_sexp(gt(sym1, num1)); printf("\n");
        printf("gt(5, a)         -> "); print_sexp(gt(sym1, num1)); printf("\n");
        printf("gte(10, 5)       -> "); print_sexp(gte(num1, num2)); printf("\n");
        printf("gte(10, 10)      -> "); print_sexp(gte(num1, num1)); printf("\n");
        printf("lt(10, 5)        -> "); print_sexp(lt(num1, num2)); printf("\n");
        printf("lte(5, 10)       -> "); print_sexp(lte(num1, num2)); printf("\n");
        printf("eq(foo, foo)     -> "); print_sexp(eq(sym1, make_symbol("foo"))); printf("\n");
        printf("eq(foo, bar)     -> "); print_sexp(eq(sym1, make_symbol("bar"))); printf("\n");
        printf("eq(foo, 1)       -> "); print_sexp(eq(sym1, make_number(5))); printf("\n");
        printf("not(nil)         -> "); print_sexp(not_op(NIL)); printf("\n");
        printf("not(T)           -> "); print_sexp(not_op(T)); printf("\n");


        printf("\nArithmetic on Non-Numbers Test Cases:\n");
        printf("add(5, foo)      -> "); print_sexp(add(num1, sym1)); printf("\n");
        printf("sub(foo, 5)      -> "); print_sexp(sub(sym1, num1)); printf("\n");

        printf("\n--- Sprint 5: Eval and Built-In Functions ---\n");
        printf("(+ 1 2)                          -> "); print_sexp(eval(sexp("(+ 1 2)"), global_env)); printf("\n");
        printf("(- 2 10)                         -> "); print_sexp(eval(sexp("(- 2 10)"), global_env)); printf("\n");
        printf("(* 6 7)                          -> "); print_sexp(eval(sexp("(* 6 7)"), global_env)); printf("\n");
        printf("(/ 100 3)                        -> "); print_sexp(eval(sexp("(/ 100 3)"), global_env)); printf("\n");
        printf("(mod 10 3)                       -> "); print_sexp(eval(sexp("(mod 10 3)"), global_env)); printf("\n");
        printf("(eq (quote a) (quote a))         -> "); print_sexp(eval(sexp("(eq (quote a) (quote a))"), global_env)); printf("\n");
        printf("(eq (quote a) (quote b))         -> "); print_sexp(eval(sexp("(eq (quote a) (quote b))"), global_env)); printf("\n");
        printf("(gt 10 5)                        -> "); print_sexp(eval(sexp("(gt 10 5)"), global_env)); printf("\n");
        printf("(gte 5 5)                        -> "); print_sexp(eval(sexp("(gte 5 5)"), global_env)); printf("\n");
        printf("(lt 10 11)                       -> "); print_sexp(eval(sexp("(lt 10 11)"), global_env)); printf("\n");
        printf("(lte 2 1)                        -> "); print_sexp(eval(sexp("(lte 2 1)"), global_env)); printf("\n");
        printf("(not nil)                        -> "); print_sexp(eval(sexp("(not nil)"), global_env)); printf("\n");
        printf("(not T)                          -> "); print_sexp(eval(sexp("(not T)"), global_env)); printf("\n");
        printf("(+ 10 (* 2 5))                   -> "); print_sexp(eval(sexp("(+ 10 (* 2 5))"), global_env)); printf("\n");
        printf("(not (eq (quote a) (quote b)))   -> "); print_sexp(eval(sexp("(not (eq (quote a) (quote b)))"), global_env)); printf("\n");
        printf("(/ 10 0)                         -> "); print_sexp(eval(sexp("(/ 10 0)"), global_env)); printf("\n");
        printf("(+ 10 (quote a))                 -> "); print_sexp(eval(sexp("(+ 10 (quote a))"), global_env)); printf("\n");

        printf("\n--- Sprint 6: Conditionals and Special Forms ---\n");
        printf("(quote hello)                     -> "); print_sexp(eval(sexp("(quote hello)"), global_env)); printf("\n");
        printf("(quote (+ 1 2))                   -> "); print_sexp(eval(sexp("(quote (+ 1 2))"), global_env)); printf("\n");
        printf("(set x 100)                       -> "); print_sexp(eval(sexp("(set x 100)"), global_env)); printf("\n");
        printf("x                                 -> "); print_sexp(eval(sexp("x"), global_env)); printf("\n");
        printf("(if (gt 10 5) 'yes 'no)           -> "); print_sexp(eval(sexp("(if (gt 10 5) 'yes 'no)"), global_env)); printf("\n");
        printf("(if (lt 10 5) 'yes 'no)           -> "); print_sexp(eval(sexp("(if (lt 10 5) 'yes 'no)"), global_env)); printf("\n");
        printf("(if (eq (mod 10 2) 0) 'even 'odd) -> "); print_sexp(eval(sexp("(if (eq (mod 10 2) 0) 'even 'odd)"), global_env)); printf("\n");

        printf("\n--- Sprint 7: Lambda, Define, and Function Application ---\n");
        printf("(define square (lambda (n) (* n n))) -> "); print_sexp(eval(sexp("(define square (lambda (n) (* n n)))"), global_env)); printf("\n");
        printf("(square 8)                        -> "); print_sexp(eval(sexp("(square 8)"), global_env)); printf("\n");
        printf("(define power (lambda (b e) (if (eq e 0) 1 (* b (power b (- e 1)))))) -> "); print_sexp(eval(sexp("(define power (lambda (b e) (if (eq e 0) 1 (* b (power b (- e 1))))))"), global_env)); printf("\n");
        printf("(power 2 10)                      -> "); print_sexp(eval(sexp("(power 2 10)"), global_env)); printf("\n");
        printf("((lambda (x) (+ x 10)) 5)         -> "); print_sexp(eval(sexp("((lambda (x) (+ x 10)) 5)"), global_env)); printf("\n");
        printf("(set my-adder (lambda (a b) (+ a b))) -> "); print_sexp(eval(sexp("(set my-adder (lambda (a b) (+ a b)))"), global_env)); printf("\n");
        printf("(my-adder 50 25)                  -> "); print_sexp(eval(sexp("(my-adder 50 25)"), global_env)); printf("\n");
        printf("(define get-five (lambda () 5))   -> "); print_sexp(eval(sexp("(define get-five (lambda () 5))"), global_env)); printf("\n");
        printf("(get-five)                        -> "); print_sexp(eval(sexp("(get-five)"), global_env)); printf("\n");


    }
    
    // REPL
    if (mode == 'R') {

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
    }
    return 0;
}