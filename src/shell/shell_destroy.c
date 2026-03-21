/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** Shell lifecycle helpers (initialization/destruction)
*/
#include <stdlib.h>

#include "shell.h"
#include "env.h"

void shell_destroy(shell_t *shell)
{
    if (!shell)
        return;
    if (shell->line) {
        free(shell->line);
        shell->line = NULL;
    }
    if (shell->env) {
        free_env(shell->env);
        shell->env = NULL;
    }
    free(shell);
}
