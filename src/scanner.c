#include "tree_sitter/parser.h"
#include "wctype.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

enum {
    SEPARATOR,
    BACKSLASH,
    FLOAT,
    BLOCK_COMMENT,
};

#define TSDEBUG 0

#if TSDEBUG
#    define DEBUG(...) fprintf(stderr, __VA_ARGS__)
#else
#    define DEBUG(...)
#endif

void *tree_sitter_odin_external_scanner_create() { return NULL; }

void tree_sitter_odin_external_scanner_destroy(void *payload) {}

unsigned tree_sitter_odin_external_scanner_serialize(void *payload,
                                                     char *buffer) {
    return 0;
}

void tree_sitter_odin_external_scanner_deserialize(void       *payload,
                                                   const char *buffer,
                                                   unsigned    length) {}

static void advance(TSLexer *lexer) { lexer->advance(lexer, false); }

static void skip(TSLexer *lexer) { lexer->advance(lexer, true); }

char next_word[] = "\0\0\0\0\0";

static void reset() { memset(next_word, 0, 6 * sizeof(char)); }

bool tree_sitter_odin_external_scanner_scan(void *payload, TSLexer *lexer,
                                            const bool *valid_symbols) {
    // newline, ;, and \0 are valid but \n is only valid if the next word isnt
    // where

    if (valid_symbols[FLOAT]) {
        while (iswspace(lexer->lookahead) && lexer->lookahead != '\n')
            skip(lexer);

        if (!valid_symbols[SEPARATOR]) // skip newlines too
            while (iswspace(lexer->lookahead))
                skip(lexer);

        // basically, -? [0-9]+ \. [0-9]*, BUT a second . after isnt allowed
        // cuz it could be ..< operator,
        // it can have an i at the end for imaginary numbers
        // and exponents, [eE][+-]?[0-9]+, imaginary comes after

        // needs ONE of these two to be float
        bool found_decimal = false;
        bool found_exponent = false;
        bool found_number_before_decimal = false;
        bool found_number_after_decimal = false;
        bool found_number_after_expontent = false;
        for (int i = 0;; i++) {
            switch (lexer->lookahead) {
                case '.':
                    if ((found_decimal || found_exponent) &&
                        (found_number_after_decimal ||
                         found_number_before_decimal)) {
                        lexer->result_symbol = FLOAT;
                        lexer->mark_end(lexer);
                        return true;
                    } else {
                        lexer->mark_end(lexer);
                        found_decimal = true;
                        advance(lexer);
                        if (lexer->lookahead == '.') {
                            advance(lexer);
                            goto separator;
                        }
                        lexer->mark_end(lexer);
                        if (!isdigit(lexer->lookahead) &&
                            (found_number_after_decimal ||
                             found_number_before_decimal)) {
                            lexer->result_symbol = FLOAT;
                            return true;
                        }
                    }
                    break;
                case 'i':
                case 'j':
                case 'k':
                    if (!found_number_after_decimal)
                        goto separator;
                    if ((found_decimal || found_exponent) &&
                        (found_number_after_decimal ||
                         found_number_before_decimal)) {
                        advance(lexer);
                        lexer->result_symbol = FLOAT;
                        lexer->mark_end(lexer);
                        return true;
                    } else {
                        goto separator;
                    }
                case 'e':
                case 'E':
                    if ((found_exponent) && (found_number_after_decimal ||
                                             found_number_before_decimal)) {
                        lexer->result_symbol = FLOAT;
                        lexer->mark_end(lexer);
                        return true;
                    } else if (found_number_before_decimal ||
                               found_number_after_decimal) {
                        found_exponent = true;
                        advance(lexer);
                    } else {
                        goto separator;
                    }
                    break;
                case '+':
                case '-':
                    if (i == 0)
                        advance(lexer);
                    else if (found_exponent && !found_number_after_expontent)
                        advance(lexer);
                    else
                        goto separator;
                    break;
                default:
                    if (isdigit(lexer->lookahead)) {
                        advance(lexer);
                        if (found_decimal) {
                            found_number_after_decimal = true;
                        } else {
                            found_number_before_decimal = true;
                        }
                        if (found_exponent && !found_number_after_expontent) {
                            found_number_after_expontent = true;
                        }
                    } else {
                        if ((found_decimal || found_exponent) &&
                            (found_number_after_decimal ||
                             found_number_before_decimal)) {
                            lexer->result_symbol = FLOAT;
                            lexer->mark_end(lexer);
                            return true;
                        } else if (found_number_before_decimal) {
                            return false; // number needs to match
                        } else if (iswspace(lexer->lookahead)) {
                            goto separator;
                            /* return false; */
                        } else {
                            goto separator;
                        }
                    }
            }
        }
    }

separator:
    if (valid_symbols[SEPARATOR]) {
        while (iswspace(lexer->lookahead) && lexer->lookahead != '\n')
            skip(lexer);

        if (lexer->lookahead == '\n') {
            advance(lexer);
            lexer->result_symbol = SEPARATOR;
            lexer->mark_end(lexer);

            while (iswspace(lexer->lookahead)) {
                skip(lexer);
            }

            const char *where = "where";
            const char *_else = "else";
            reset();

            // check for where and _else

            for (int i = 0; i < 5; i++) {
                if (iswspace(lexer->lookahead))
                    break;
                next_word[i] = lexer->lookahead;
                advance(lexer);
            }

            if (strcmp(next_word, where) == 0 ||
                strcmp(next_word, _else) == 0) {
                if (!iswspace(lexer->lookahead))
                    return true;
                else
                    goto backslash;
            }

            return true;
        } else if (lexer->lookahead == ';') {
            advance(lexer);
            lexer->result_symbol = SEPARATOR;
            lexer->mark_end(lexer);
            while (iswspace(lexer->lookahead))
                advance(lexer);
            return true;
        }
    }

backslash:
    if (valid_symbols[BACKSLASH] && lexer->lookahead == '\\') {
        advance(lexer);
        if (lexer->lookahead == '\n') {
            advance(lexer);
            while (iswspace(lexer->lookahead)) {
                advance(lexer);
            }
            lexer->result_symbol = BACKSLASH;
            return true;
        }
    }

    while (iswspace(lexer->lookahead))
        skip(lexer);

    if (valid_symbols[BLOCK_COMMENT] && lexer->lookahead == '/') {
        advance(lexer);
        if (lexer->lookahead != '*')
            return false;
        advance(lexer);

        if (lexer->lookahead == '"')
            return false;

        bool     after_star = false;
        unsigned nesting_depth = 1;
        for (;;) {
            switch (lexer->lookahead) {
                case '\0':
                    return false;
                case '*':
                    advance(lexer);
                    after_star = true;
                    break;
                case '/':
                    if (after_star) {
                        advance(lexer);
                        after_star = false;
                        nesting_depth--;
                        if (nesting_depth == 0) {
                            lexer->result_symbol = BLOCK_COMMENT;
                            return true;
                        }
                    } else {
                        advance(lexer);
                        after_star = false;
                        if (lexer->lookahead == '*') {
                            nesting_depth++;
                            advance(lexer);
                        }
                    }
                    break;
                default:
                    advance(lexer);
                    after_star = false;
                    break;
            }
        }
    }

    return false;
}
