/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** Interactive/non-interactive read-execute loop
*/
#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#include "loop.h"
#include "utils.h"

static int show_prompt(shell_t *shell)
{
    if (!shell || !shell->interactive)
        return SUCCESS;
    if (write(1, "$> ", 3) == -1)
        return ERROR;
    return SUCCESS;
}

static void trim_newline(char *buffer, ssize_t input)
{
    if (!buffer || input <= 0)
        return;
    if (buffer[input - 1] == '\n')
        buffer[input - 1] = '\0';
}

static int handle_read_failure(void)
{
    if (feof(stdin))
        return SUCCESS;
    if (errno == EINTR) {
        clearerr(stdin);
        return 1;
    }
    return ERROR;
}

static int handle_input(shell_t *shell, ssize_t input)
{
    int failure = SUCCESS;

    if (!shell)
        return ERROR;
    if (input == -1) {
        failure = handle_read_failure();
        if (failure == 1)
            return 1;
        if (failure == ERROR)
            return ERROR;
        return 2;
    }
    trim_newline(shell->line, input);
    if (!shell->line || shell->line[0] == '\0')
        return 1;
    if (my_strcmp(shell->line, "exit") == 0)
        return 2;
    if (my_exec(shell, shell->line) == ERROR)
        return ERROR;
    return SUCCESS;
}

int shell_run(shell_t *shell)
{
    ssize_t input = 0;
    int prompt_status = 0;
    int status = SUCCESS;

    if (!shell)
        return ERROR;
    while (1) {
        prompt_status = show_prompt(shell);
        if (prompt_status == ERROR)
            return ERROR;
        input = getline(&shell->line, &shell->line_cap, stdin);
        status = handle_input(shell, input);
        if (status == ERROR)
            return ERROR;
        if (status == 1)
            continue;
        if (status == 2)
            break;
    }
    return shell->last_status;
}
