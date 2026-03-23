/*
** EPITECH PROJECT, 2026
** G-PSU-200-MPL-2-1-minishell2-15
** File description:
** lexer_destroy
*/

#include "lexer.h"
#include <stdlib.h>

void lexer_destroy(lexer_t *lexer)
{
    if (!lexer)
        return;
    for (size_t i = 0; i < lexer->token_count; i++) {
        if (lexer->tokens[i])
            token_destroy(lexer->tokens[i]);
    }
    if (lexer->tokens)
        free(lexer->tokens);
    free(lexer);
}
