/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** Environment initialization helpers for mysh
*/
#include "my.h"

char **init_shell_env(char **env)
{
    char *default_nlspath = "/usr/share/locale/%L/LC_MESSAGES/%N.cat:"
        "/usr/share/locale/%l/LC_MESSAGES/%N.cat";

    env = remove_env_key(env, "OLDPWD");
    if (find_env_index(env, "NLSPATH") == -1)
        env = update_env(env, "NLSPATH", default_nlspath);
    return env;
}
