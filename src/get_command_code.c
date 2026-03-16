/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** Substitution of $? by previous command exit code
*/
#include "my.h"

char **get_command_code(char **array, int code)
{
    for (int i = 0; array[i]; i++) {
        if (my_strcmp(array[i], "$?") == 0) {
            free(array[i]);
            array[i] = my_int_to_str(code);
        }
    }
    return array;
}
