/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** Command parsing helpers
*/
#include <stddef.h>

#include "loop.h"
#include "my_utils.h"

static size_t count_args(char **argv)
{
    size_t count = 0;

    if (!argv)
        return 0;
    while (argv[count])
        count++;
    return count;
}

int command_init(command_t *cmd, char const *line)
{
    if (!cmd || !line)
        return ERROR;
    cmd->argv = NULL;
    cmd->argc = 0;
    cmd->argv = str_to_word_array(line, ' ');
    if (!cmd->argv)
        return ERROR;
    cmd->argc = count_args(cmd->argv);
    return SUCCESS;
}
