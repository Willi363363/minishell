/*
** EPITECH PROJECT, 2026
** G-PSU-200-MPL-2-1-minishell2-15
** File description:
** remove_env_key
*/

#include <stdlib.h>

#include "env.h"

static int copy_without_index(char **new_env, char **env, int count, int index)
{
    int pos = 0;

    for (int i = 0; i < count; i++) {
        if (i == index)
            free(env[i]);
        else {
            new_env[pos] = env[i];
            pos++;
        }
    }
    new_env[pos] = NULL;
    return pos;
}

char **remove_env_key(char **env, char const *key)
{
    int index = find_env_index(env, key);
    int count = count_env(env);
    char **new_env = NULL;

    if (index == -1)
        return env;
    new_env = malloc(sizeof(char *) * count);
    if (!new_env)
        return env;
    copy_without_index(new_env, env, count, index);
    free(env);
    return new_env;
}
