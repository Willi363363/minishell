/*
** EPITECH PROJECT, 2026
** G-PSU-200-MPL-2-1-minishell2-15
** File description:
** lexer_create
*/

#include "lexer.h"
#include <stdlib.h>

lexer_t *lexer_create(void)
{
    lexer_t *lexer = malloc(sizeof(lexer_t));

    if (!lexer)
        return NULL;
    lexer->tokens = NULL;
    lexer->token_count = 0;
    lexer->next = NULL;
    return lexer;
}
