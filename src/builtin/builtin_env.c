/*
** EPITECH PROJECT, 2026
** G-PSU-200-MPL-2-1-minishell2-15
** File description:
** builtin_env
*/

#include <stddef.h>

#include "builtin.h"
#include "env.h"
#include "my_utils.h"

int builtin_env(shell_t *shell, command_t *cmd)
{
    if (!shell || !cmd)
        return ERROR;
    if (cmd->argc > 1) {
        if (put_on_fd(2, "env: Too many arguments.\n") == ERROR)
            return ERROR;
        return 1;
    }
    return print_env(shell);
}
