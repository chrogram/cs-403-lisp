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
    double y = 1.0005;

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

    SExp *head = NULL, *tail = NULL, *current = NULL;
    head = cons(parse_sexp(input), NIL);
    current = head;

    while (1) {
        skip_whitespace(input);
        if (**input == ')') {
            (*input)++; // Skip ')'
            break;
        }
        if (**input == '\0') {
            // Unmatched parenthesis
            // Depending on desired error handling, you might want to free memory and return NULL
            break; 
        }

        tail = cons(parse_sexp(input), NIL);
        // current->pair.cdr = tail;
        current->data.cons.cdr = tail;
        current = tail;
    }

    return head;
}

static SExp* parse_sexp(const char** input) {
    // printf("here\n");
    skip_whitespace(input);
    // printf("Current input:: %s\n", *input);
    if (**input == '\0'){
        // printf("End of input reached unexpectedly.\n");
        return NULL;
    }
    if (**input == '(') {
        // printf("Parsing list starting at: %s\n", *input);
        return parse_list(input);
    }
    if (**input == '"') {
        // printf("Parsing string starting at: %s\n", *input);
        return parse_string(input);
    }
    // printf("Parsing atom starting at: %s\n", *input);
    return parse_atom(input);
}

SExp* sexp(const char* input_str) {
    const char* p = input_str;
    // printf("Start Parsing: %s\n", input_str);
    return parse_sexp(&p);
}