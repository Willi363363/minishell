/*
** EPITECH PROJECT, 2026
** G-PSU-200-MPL-2-1-minishell2-15
** File description:
** shell_create
*/

#include <stdlib.h>
#include <unistd.h>

#include "shell.h"

shell_t *shell_create(void)
{
    shell_t *shell = malloc(sizeof(shell_t));

    if (!shell)
        return NULL;
    shell->env = NULL;
    shell->last_status = 0;
    shell->interactive = isatty(STDIN_FILENO);
    shell->line = NULL;
    shell->line_cap = 0;
    return shell;
}
