/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** Interactive/non-interactive read-execute loop
*/
#include "my.h"

static int read_command(char **buffer, size_t *bufsize, int interactive)
{
    if (interactive && write(1, "$> ", 3) < 0)
        return -2;
    return getline(buffer, bufsize, stdin);
}

static void trim_newline(char *buffer, int input)
{
    if (input > 0 && buffer[input - 1] == '\n')
        buffer[input - 1] = '\0';
}

int loop_terminal(char ***env, int value, int input, size_t bufsize)
{
    char *buffer = NULL;
    int interactive = isatty(STDIN_FILENO);

    while (1) {
        input = read_command(&buffer, &bufsize, interactive);
        if (input == -2) {
            free(buffer);
            return 84;
        }
        if (input == -1)
            break;
        trim_newline(buffer, input);
        if (buffer[0] == '\0')
            continue;
        if (my_strcmp(buffer, "exit") == 0)
            break;
        value = my_exec(buffer, env, value);
    }
    free(buffer);
    return value;
}
