/*
** EPITECH PROJECT, 2026
** G-PSU-200-MPL-2-1-minishell2-15
** File description:
** token_create
*/

#include "token.h"
#include <stdlib.h>
#include <string.h>

token_t *token_create(token_type_t type, const char *value)
{
    token_t *token = NULL;

    if (type < TOK_ARGS || type > TOK_EOF || !value)
        return NULL;
    token = malloc(sizeof(token_t));
    if (!token)
        return NULL;
    token->type = type;
    token->value = value ? strdup(value) : NULL;
    return token;
}
