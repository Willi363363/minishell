/*
** EPITECH PROJECT, 2026
** G-PSU-200-MPL-2-1-minishell2-15
** File description:
** env
*/

#ifndef ENV_H_
    #define ENV_H_

    #include "loop.h"

int count_env(char **env);
int find_env_index(char **env, char const *key);
char **dup_env(char **env);
void free_env(char **env);
char **remove_env_key(char **env, char const *key);
char **update_env(char **env, char const *key, char const *value);
char **init_shell_env(char **env);
int print_env(shell_t *shell);
int my_unsetenv(shell_t *shell, command_t *cmd);

#endif /* !ENV_H_ */
