/*
** EPITECH PROJECT, 2026
** G-PSU-200-MPL-2-1-minishell2-15
** File description:
** shell_init
*/

#include <stddef.h>
#include <unistd.h>

#include "shell.h"
#include "env.h"

static void shell_reset(shell_t *shell)
{
    shell->env = NULL;
    shell->last_status = 0;
    shell->interactive = isatty(STDIN_FILENO);
    shell->line = NULL;
    shell->line_cap = 0;
}

int shell_init(shell_t *shell, char **env)
{
    if (!shell)
        return ERROR;
    shell_reset(shell);
    shell->env = dup_env(env);
    if (!shell->env)
        return ERROR;
    shell->env = init_shell_env(shell->env);
    if (!shell->env)
        return ERROR;
    return SUCCESS;
}
