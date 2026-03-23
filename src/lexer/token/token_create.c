/*
** EPITECH PROJECT, 2026
** G-PSU-200-MPL-2-1-minishell2-15
** File description:
** token_create
*/

#include "token.h"
#include <stdlib.h>

static char *dup_slice(const char *value, size_t len)
{
    char *out = NULL;
    size_t i = 0;

    out = malloc((len + 1) * sizeof(char));
    if (!out)
        return NULL;
    while (i < len) {
        out[i] = value[i];
        i++;
    }
    out[len] = '\0';
    return out;
}

token_t *token_create(token_type_t type, const char *value, size_t len)
{
    token_t *token = NULL;

    if (type < TOK_ARGS || type > TOK_EOF || !value)
        return NULL;
    token = malloc(sizeof(token_t));
    if (!token)
        return NULL;
    token->type = type;
    token->value = dup_slice(value, len);
    token->next = NULL;
    if (!token->value) {
        free(token);
        return NULL;
    }
    return token;
}
