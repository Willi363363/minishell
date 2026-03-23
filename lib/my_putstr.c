/*
** EPITECH PROJECT, 2025
** my_putstr
** File description:
** Prints a string to stdout
*/
#include "my_utils.h"

int my_putstr(char const *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (my_putchar(str[i]) != 0)
            return 84;
    }
    return 0;
}
