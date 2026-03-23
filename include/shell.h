/*
** EPITECH PROJECT, 2026
** G-PSU-200-MPL-2-1-minishell2-15
** File description:
** shell
*/

#ifndef SHELL_H_
    #define SHELL_H_
    #include <stddef.h>

    #include "my_utils.h"

typedef struct shell_s {
    char **env;
    int last_status;
    int interactive;
    char *line;
    size_t line_cap;
} shell_t;

shell_t *shell_create(void);
int shell_init(shell_t *shell, char **env);
void shell_destroy(shell_t *shell);

#endif /* !SHELL_H_ */
