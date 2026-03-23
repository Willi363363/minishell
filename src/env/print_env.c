/*
** EPITECH PROJECT, 2026
** G-PSU-200-MPL-2-1-minishell2-15
** File description:
** print_env
*/

#include <stddef.h>

#include "env.h"
#include "my_utils.h"

int print_env(shell_t *shell)
{
    if (!shell || !shell->env)
        return 0;
    for (int i = 0; shell->env[i]; i++) {
        if (put_on_fd(1, shell->env[i]) == ERROR
            || put_on_fd(1, "\n") == ERROR)
            return ERROR;
    }
    return SUCCESS;
}
