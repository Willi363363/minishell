/*
** EPITECH PROJECT, 2025
** my_putchar
** File description:
** Prints a character to stdout
*/

#include <unistd.h>

#include "utils.h"

int my_putchar(char c)
{
    if (write(1, &c, 1) == -1)
        return 84;
    return 0;
}
