#ifndef PARSER_H
#define PARSER_H

#include "sexp.h"

/**
 * @brief Parses a string and creates the correct type of S-Expression.
 * @param input_str The null-terminated string to parse.
 * @return A pointer to the parsed S-Expression, or NULL on error.
 */
SExp* sexp(const char* input_str);

#endif // PARSER_H