/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** Substitution of $? by previous command exit code
*/
#include <stddef.h>
#include <stdlib.h>

#include "loop.h"
#include "my_utils.h"

int get_command_code(command_t *cmd, int code)
{
    char *replacement = NULL;

    if (!cmd || !cmd->argv)
        return ERROR;
    for (size_t i = 0; cmd->argv[i]; i++) {
        if (my_strcmp(cmd->argv[i], "$?") != 0)
            continue;
        replacement = my_int_to_str(code);
        if (!replacement)
            return ERROR;
        free(cmd->argv[i]);
        cmd->argv[i] = replacement;
    }
    return SUCCESS;
}
