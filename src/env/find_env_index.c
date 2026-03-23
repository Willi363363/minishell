/*
** EPITECH PROJECT, 2026
** G-PSU-200-MPL-2-1-minishell2-15
** File description:
** find_env_index
*/

#include <stddef.h>

#include "env.h"
#include "my_utils.h"

int find_env_index(char **env, char const *key)
{
    int i = 0;
    int key_len = 0;

    if (!env || !key)
        return -1;
    key_len = my_strlen(key);
    while (env[i]) {
        if (my_strncmp(env[i], key, key_len) == 0 && env[i][key_len] == '=')
            return i;
        i++;
    }
    return -1;
}
