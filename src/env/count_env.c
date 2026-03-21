/*
** EPITECH PROJECT, 2026
** G-PSU-200-MPL-2-1-minishell2-15
** File description:
** count_env
*/

#include <stddef.h>

#include "env.h"

int count_env(char **env)
{
    int count = 0;

    if (!env)
        return 0;
    while (env[count])
        count++;
    return count;
}
