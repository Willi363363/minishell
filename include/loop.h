/*
** EPITECH PROJECT, 2026
** G-PSU-200-MPL-2-1-minishell2-15
** File description:
** loop
*/

#ifndef LOOP_H_
    #define LOOP_H_
    #include <stddef.h>

    #include "shell.h"

typedef struct command_s {
    char **argv;
    size_t argc;
} command_t;

int command_init(command_t *cmd, char const *line);
void command_destroy(command_t *cmd);
int get_command_code(command_t *cmd, int code);
int fork_process(char **array, char **env);
int my_exec(shell_t *shell, char const *buffer);
int exec_command(shell_t *shell, char **argv);
int shell_run(shell_t *shell);

#endif /* !LOOP_H_ */
