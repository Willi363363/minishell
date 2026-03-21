/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** Environment initialization helpers for mysh
*/
#include <stddef.h>

#include "env.h"

char **init_shell_env(char **env)
{
    char *default_nlspath = "/usr/share/locale/%L/LC_MESSAGES/%N.cat:"
        "/usr/share/locale/%l/LC_MESSAGES/%N.cat";
    char **updated = NULL;

    env = remove_env_key(env, "OLDPWD");
    if (!env)
        return NULL;
    if (find_env_index(env, "NLSPATH") == -1) {
        updated = update_env(env, "NLSPATH", default_nlspath);
        if (!updated) {
            free_env(env);
            return NULL;
        }
        env = updated;
    }
    return env;
}
