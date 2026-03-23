/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** unsetenv builtin implementation
*/
#include <stddef.h>
#include <stdlib.h>

#include "env.h"
#include "my_utils.h"

static void copy_without_key(char **dest, char **src, int count, int index)
{
    int pos = 0;

    for (int i = 0; i < count; i++) {
        if (i == index) {
            free(src[i]);
            continue;
        }
        dest[pos] = src[i];
        pos++;
    }
    dest[pos] = NULL;
}

static char **unset_function(char **env, char *key)
{
    int index = 0;
    int count = count_env(env);
    char **new_env = NULL;

    if (!env || count == 0)
        return env;
    index = find_env_index(env, key);
    if (index == -1)
        return env;
    new_env = malloc(sizeof(char *) * count);
    if (!new_env)
        return env;
    copy_without_key(new_env, env, count, index);
    free(env);
    return new_env;
}

static int unset_one_key(shell_t *shell, char *key)
{
    if (my_strcmp(key, "*") == 0) {
        if (put_on_fd(2, "unsetenv: Wildcards not allowed.\n") == ERROR)
            return ERROR;
        return 1;
    }
    shell->env = unset_function(shell->env, key);
    if (!shell->env)
        return ERROR;
    return SUCCESS;
}

int my_unsetenv(shell_t *shell, command_t *cmd)
{
    int status = SUCCESS;

    if (!shell || !cmd || cmd->argc == 0)
        return ERROR;
    if (cmd->argc == 1) {
        if (put_on_fd(2, "unsetenv: Too few arguments.\n") == ERROR)
            return ERROR;
        return 1;
    }
    for (size_t i = 1; i < cmd->argc; i++) {
        status = unset_one_key(shell, cmd->argv[i]);
        if (status == ERROR)
            return ERROR;
        if (status != 0)
            return status;
    }
    return SUCCESS;
}
