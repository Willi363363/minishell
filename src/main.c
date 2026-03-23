/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** Program entry point and shell lifecycle
*/
#include <stddef.h>

#include "shell.h"
#include "loop.h"

int main(int argc, char **argv, char **env)
{
    shell_t *shell = NULL;
    int status = SUCCESS;

    if (argc != 1 || !argv)
        return ERROR;
    shell = shell_create();
    if (!shell)
        return ERROR;
    if (shell_init(shell, env) == ERROR)
        return ERROR;
    status = shell_run(shell);
    shell_destroy(shell);
    return status;
}
