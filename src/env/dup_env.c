/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** Environment duplication utilities
*/
#include <stddef.h>
#include <stdlib.h>

#include "env.h"
#include "my_utils.h"

static size_t env_length(char **env)
{
    size_t len = 0;

    if (!env)
        return 0;
    while (env[len])
        len++;
    return len;
}

static void free_partial_env(char **env, size_t last)
{
    while (last != (size_t)-1) {
        free(env[last]);
        if (last == 0)
            break;
        last--;
    }
    free(env);
}

char **dup_env(char **env)
{
    size_t len = env_length(env);
    char **new_env = malloc(sizeof(char *) * (len + 1));

    if (!new_env)
        return NULL;
    for (size_t i = 0; i < len; i++) {
        new_env[i] = my_strdup(env[i]);
        if (!new_env[i]) {
            free_partial_env(new_env, i);
            return NULL;
        }
    }
    new_env[len] = NULL;
    return new_env;
}
