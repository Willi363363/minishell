/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** Implementation of cd path switching and PWD/OLDPWD updates
*/
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "builtin.h"
#include "env.h"
#include "my_utils.h"

static int put_cd_errno(char *path)
{
    if (put_on_fd(2, path) == ERROR)
        return ERROR;
    if (put_on_fd(2, ": ") == ERROR)
        return ERROR;
    if (put_on_fd(2, strerror(errno)) == ERROR)
        return ERROR;
    if (put_on_fd(2, ".\n") == ERROR)
        return ERROR;
    return 1;
}

static char *find_env_value(char **env, char *name)
{
    int i = 0;
    int len = my_strlen(name);

    while (env[i]) {
        if (my_strncmp(env[i], name, len) == 0 && env[i][len] == '=')
            return env[i] + len + 1;
        i++;
    }
    return NULL;
}

static int set_env_path(shell_t *shell, char const *key, char *path)
{
    char **updated = NULL;

    if (!shell || !key || !path)
        return ERROR;
    updated = update_env(shell->env, key, path);
    free(path);
    if (!updated)
        return ERROR;
    shell->env = updated;
    return SUCCESS;
}

static int update_pwd(shell_t *shell, char *old_path)
{
    char *new_path = NULL;

    if (!shell)
        return ERROR;
    if (old_path && set_env_path(shell, "OLDPWD", old_path) == ERROR)
        return ERROR;
    new_path = getcwd(NULL, 0);
    if (!new_path)
        return ERROR;
    return set_env_path(shell, "PWD", new_path);
}

static int cd_home(shell_t *shell, char *home)
{
    char *old_path = NULL;

    if (!home) {
        if (put_on_fd(2, "cd: HOME not set.\n") == ERROR)
            return ERROR;
        return 1;
    }
    old_path = getcwd(NULL, 0);
    if (chdir(home) != 0) {
        free(old_path);
        return put_cd_errno(home);
    }
    return update_pwd(shell, old_path);
}

static int cd_oldpwd(shell_t *shell, char *old)
{
    char *old_path = NULL;

    if (!old) {
        if (put_on_fd(2, "cd: OLDPWD not set.\n") == ERROR)
            return ERROR;
        return 1;
    }
    old_path = getcwd(NULL, 0);
    if (chdir(old) != 0) {
        free(old_path);
        return put_cd_errno(old);
    }
    return update_pwd(shell, old_path);
}

static int cd_to_path(shell_t *shell, char *path)
{
    char *old_path = getcwd(NULL, 0);

    if (chdir(path) != 0) {
        free(old_path);
        return put_cd_errno(path);
    }
    return update_pwd(shell, old_path);
}

int cd_command(shell_t *shell, command_t *cmd)
{
    char *home = NULL;
    char *old = NULL;

    if (!shell || !cmd || cmd->argc == 0)
        return ERROR;
    home = find_env_value(shell->env, "HOME");
    old = find_env_value(shell->env, "OLDPWD");
    if (cmd->argc > 2) {
        if (put_on_fd(2, "cd: Too many arguments.\n") == ERROR)
            return ERROR;
        return 1;
    }
    if (cmd->argc == 1 || my_strcmp(cmd->argv[1], "~") == 0)
        return cd_home(shell, home);
    if (my_strcmp(cmd->argv[1], "-") == 0)
        return cd_oldpwd(shell, old);
    return cd_to_path(shell, cmd->argv[1]);
}
