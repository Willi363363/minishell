/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** cd builtin wrapper
*/
#include "my.h"

int cd_command(char **array, char ***env, int value)
{
    char *home = NULL;
    char *old = NULL;

    value = change_directory(array, env, home, old);
    return value;
}
