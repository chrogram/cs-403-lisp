#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "sexp.h"

SExp* sexp(const char* input_str);

// Forward declarations for recursive parsing
static SExp* parse_sexp(const char** input);

static void skip_whitespace(const char** input) {
    if (input == NULL || *input == NULL) return;
    while (isspace(**input)) (*input)++;
}

static SExp* parse_atom(const char** input) {
    char buffer[256];
    int i = 0;

    while (**input && !isspace(**input) && **input != ')' && **input != '(' && i < 255) {
        buffer[i++] = *(*input)++;
    }
    buffer[i] = '\0';

    char* end;
    double val = strtod(buffer, &end);
    if (*end == '\0' && (isdigit(buffer[0]) || (buffer[0] == '-' && isdigit(buffer[1])))) {
        return make_number(val);
    }
    return make_symbol(buffer);
}

static SExp* parse_string(const char** input) {
    (*input)++; // Skip opening quote
    char buffer[1024];
    int i = 0;
    while (**input && **input != '"' && i < 1023) {
        buffer[i++] = *(*input)++;
    }
    buffer[i] = '\0';
    if (**input == '"') (*input)++; // Skip closing quote
    return make_string(buffer);
}

static SExp* parse_list(const char** input) {
    (*input)++; // Skip '('
    skip_whitespace(input);
    if (**input == ')') {
        (*input)++; // Skip ')' for an empty list
        return NIL;
    }

    SExp *head = cons(parse_sexp(input), NIL);
    SExp *current = head;

    while (1) {
        skip_whitespace(input);

        if (**input == ')') {
            (*input)++; // Skip ')'
            return head;
        }

        if (**input == '\0') {
            fprintf(stdout, "Error: Unmatched opening parenthesis.\n");
            // A free_sexp(head) call would be needed here to prevent memory leaks.
            return NULL; 
        }

        if (**input == '.') {
            (*input)++; // Consume '.'
            skip_whitespace(input);
            current->data.cons.cdr = parse_sexp(input);
            skip_whitespace(input);
            if (**input != ')') {
                fprintf(stdout, "Error: Expected ')' after dotted pair.\n");
                // Memory cleanup would be needed here.
                return NULL;
            }
            (*input)++; // Consume ')'
            return head;
        }

        SExp* new_cell = cons(parse_sexp(input), NIL);
        current->data.cons.cdr = new_cell;
        current = new_cell;
    }
}

static SExp* parse_sexp(const char** input) {
    skip_whitespace(input);
    if (**input == '\0'){
        return NULL;
    }
    if (**input == '(') {
        return parse_list(input);
    }
    if (**input == '"') {
        return parse_string(input);
    }
    return parse_atom(input);
}

SExp* sexp(const char* input_str) {
    const char* p = input_str;
    SExp* result = parse_sexp(&p);
    
    skip_whitespace(&p);
    if (*p != '\0') {
        fprintf(stdout, "Error: Unexpected trailing characters: %s\n", p);
        return NULL;
    }

    return result;
}