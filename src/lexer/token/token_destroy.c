/*
** EPITECH PROJECT, 2026
** G-PSU-200-MPL-2-1-minishell2-15
** File description:
** token_destroy
*/

#include "token.h"
#include <stdlib.h>

void token_destroy(token_t *token)
{
    if (!token)
        return;
    if (token->value)
        free(token->value);
    free(token);
}
