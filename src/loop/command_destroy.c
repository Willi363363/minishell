/*
** EPITECH PROJECT, 2026
** G-PSU-200-MPL-2-1-minishell2-15
** File description:
** command_destroy
*/

#include <stddef.h>
#include <stdlib.h>

#include "loop.h"

void command_destroy(command_t *cmd)
{
    if (!cmd || !cmd->argv)
        return;
    for (size_t i = 0; cmd->argv[i]; i++)
        free(cmd->argv[i]);
    free(cmd->argv);
    cmd->argv = NULL;
    cmd->argc = 0;
}
