/*
** EPITECH PROJECT, 2026
** G-PSU-200-MPL-2-1-minishell2-15
** File description:
** free_env
*/

#include <stddef.h>
#include <stdlib.h>

#include "env.h"

void free_env(char **env)
{
    if (!env)
        return;
    for (size_t i = 0; env[i]; i++)
        free(env[i]);
    free(env);
}
