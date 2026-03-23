/*
** EPITECH PROJECT, 2026
** lexer.h
** File description:
** Lexer header file
*/
#ifndef LEXER_H
    #define LEXER_H

    #include <stddef.h>
    #include "token.h"

typedef struct lexer_s lexer_t;

typedef struct lexer_s {
    token_t *tokens;
    size_t token_count;
    lexer_t *next;
} lexer_t;

lexer_t *lexer_create(void);
void lexer_destroy(lexer_t *lexer);
int lexer_tokenize(lexer_t *lexer, const char *input);

#endif /* LEXER_H */
