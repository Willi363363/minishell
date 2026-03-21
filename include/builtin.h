/*
** EPITECH PROJECT, 2026
** G-PSU-200-MPL-2-1-minishell2-15
** File description:
** builtin
*/

#ifndef BUILTIN_H_
    #define BUILTIN_H_

    #include "loop.h"

int builtin_env(shell_t *shell, command_t *cmd);
int builtin_setenv(shell_t *shell, command_t *cmd);
int cd_command(shell_t *shell, command_t *cmd);

#endif /* !BUILTIN_H_ */
