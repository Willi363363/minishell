/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** Builtin dispatch and external command execution entry
*/
#include <stddef.h>

#include "loop.h"
#include "builtin.h"
#include "env.h"
#include "my_utils.h"

static int handle_exec_status(int value, char *command)
{
    if (value == 127) {
        if (put_on_fd(2, command) == ERROR
            || put_on_fd(2, ": Command not found.\n") == ERROR)
            return ERROR;
        return 1;
    }
    if (value == 126) {
        if (put_on_fd(2, command) == ERROR
            || put_on_fd(2, ": Permission denied.\n") == ERROR)
            return ERROR;
        return 1;
    }
    return value;
}

static int run_builtin(shell_t *shell, command_t *cmd, int *handled)
{
    int value = 0;

    if (!handled || !shell || !cmd)
        return ERROR;
    value = shell->last_status;
    *handled = 1;
    if (my_strcmp(cmd->argv[0], "cd") == 0)
        return cd_command(shell, cmd);
    if (my_strcmp(cmd->argv[0], "setenv") == 0)
        return builtin_setenv(shell, cmd);
    if (my_strcmp(cmd->argv[0], "unsetenv") == 0)
        return my_unsetenv(shell, cmd);
    if (my_strcmp(cmd->argv[0], "env") == 0)
        return builtin_env(shell, cmd);
    *handled = 0;
    return value;
}

static int run_external(shell_t *shell, command_t *cmd, int previous_status)
{
    int value = 0;

    if (!shell || !cmd)
        return ERROR;
    if (get_command_code(cmd, previous_status) == ERROR)
        return ERROR;
    value = fork_process(cmd->argv, shell->env);
    return handle_exec_status(value, cmd->argv[0]);
}

static int dispatch_command(shell_t *shell, command_t *cmd)
{
    int handled = 0;
    int previous_status = 0;
    int value = SUCCESS;

    if (!shell || !cmd)
        return ERROR;
    previous_status = shell->last_status;
    value = run_builtin(shell, cmd, &handled);
    if (value == ERROR)
        return ERROR;
    if (handled)
        return value;
    return run_external(shell, cmd, previous_status);
}

int my_exec(shell_t *shell, char const *buffer)
{
    command_t cmd;
    int value = SUCCESS;

    if (!shell || !buffer)
        return ERROR;
    if (command_init(&cmd, buffer) == ERROR)
        return ERROR;
    if (cmd.argc == 0) {
        command_destroy(&cmd);
        return shell->last_status;
    }
    value = dispatch_command(shell, &cmd);
    command_destroy(&cmd);
    if (value != ERROR)
        shell->last_status = value;
    return value;
}

static size_t argv_len(char **argv)
{
    size_t i = 0;

    while (argv && argv[i])
        i++;
    return i;
}

int exec_command(shell_t *shell, char **argv)
{
    command_t cmd;
    int value = SUCCESS;

    if (!shell || !argv || !argv[0])
        return ERROR;
    cmd.argv = argv;
    cmd.argc = argv_len(argv);
    if (cmd.argc == 0)
        return shell->last_status;
    value = dispatch_command(shell, &cmd);
    if (value != ERROR)
        shell->last_status = value;
    return value;
}
