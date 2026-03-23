/*
** EPITECH PROJECT, 2026
** G-PSU-200-MPL-2-1-minishell2-15
** File description:
** lexer_destroy
*/

#include "lexer.h"
#include <stdlib.h>
#include "token.h"

void lexer_destroy(lexer_t *lexer)
{
    token_t *current = NULL;
    token_t *next = NULL;

    if (!lexer)
        return;
    current = lexer->tokens;
    while (current) {
        next = current->next;
        token_destroy(current);
        current = next;
    }
    lexer->tokens = NULL;
    if (lexer->next) {
        lexer_destroy(lexer->next);
        lexer->next = NULL;
    }
    free(lexer);
}
