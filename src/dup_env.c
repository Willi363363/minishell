/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** Environment duplication utilities
*/
#include "my.h"

static void free_duplicated_env(char **new_env, int last)
{
    while (last >= 0) {
        free(new_env[last]);
        last--;
    }
    free(new_env);
}

char **dup_env(char **env)
{
    int i = 0;
    int j = 0;
    char **new_env = NULL;

    while (env[i])
        i++;
    new_env = malloc(sizeof(char *) * (i + 1));
    if (!new_env)
        return NULL;
    while (j < i) {
        new_env[j] = my_strdup(env[j]);
        if (!new_env[j]) {
            free_duplicated_env(new_env, j - 1);
            return NULL;
        }
        j++;
    }
    new_env[i] = NULL;
    return new_env;
}
