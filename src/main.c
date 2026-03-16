/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** Program entry point and shell lifecycle
*/
#include "my.h"

int main(int argc, char **argv, char **env)
{
    int value = 0;
    int input = 0;
    size_t bufsize = 0;
    char **my_env = NULL;

    if (argc != 1 || !argv)
        return 84;
    my_env = dup_env(env);
    if (!my_env)
        return 84;
    my_env = init_shell_env(my_env);
    value = loop_terminal(&my_env, value, input, bufsize);
    for (int i = 0; my_env[i]; i++)
        free(my_env[i]);
    free(my_env);
    return 0;
}
