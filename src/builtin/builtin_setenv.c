/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** Builtins for env, setenv
*/
#include <stddef.h>

#include "builtin.h"
#include "env.h"
#include "my_utils.h"

static int setenv_name_error(char *message)
{
    if (put_on_fd(2, message) == ERROR)
        return ERROR;
    return 1;
}

static int validate_setenv_name(char *name)
{
    int i = SUCCESS;

    if (!name || !((name[0] >= 'A' && name[0] <= 'Z')
            || (name[0] >= 'a' && name[0] <= 'z')))
        return setenv_name_error(
            "setenv: Variable name must begin with a letter.\n");
    while (name[i]) {
        if (!((name[i] >= 'A' && name[i] <= 'Z')
                || (name[i] >= 'a' && name[i] <= 'z')
                || (name[i] >= '0' && name[i] <= '9')))
            return setenv_name_error(
                "setenv: Variable name must contain alphanumeric "
                "characters.\n");
        i++;
    }
    return SUCCESS;
}

static int handle_setenv_arity(shell_t *shell, command_t *cmd)
{
    if (cmd->argc == 1)
        return print_env(shell);
    if (cmd->argc > 3) {
        if (put_on_fd(2, "setenv: Too many arguments.\n") == ERROR)
            return ERROR;
        return 1;
    }
    return SUCCESS;
}

int builtin_setenv(shell_t *shell, command_t *cmd)
{
    int valid = 0;
    int status = 0;
    char **updated = NULL;
    char *value = "";

    if (!shell || !cmd)
        return ERROR;
    status = handle_setenv_arity(shell, cmd);
    if (status != 0)
        return status;
    valid = validate_setenv_name(cmd->argv[1]);
    if (valid != 0)
        return valid;
    value = cmd->argc == 3 ? cmd->argv[2] : "";
    updated = update_env(shell->env, cmd->argv[1], value);
    if (!updated)
        return ERROR;
    shell->env = updated;
    return SUCCESS;
}
