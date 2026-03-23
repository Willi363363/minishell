/*
** EPITECH PROJECT, 2025
** my_put_nbr
** File description:
** Prints an integer to stdout
*/
#include "my_utils.h"

int my_put_nbr(int nb)
{
    long n = nb;

    if (n < 0) {
        if (my_putchar('-') != 0)
            return 84;
        n = -n;
    }
    if (n >= 10) {
        if (my_put_nbr(n / 10) != 0)
            return 84;
    }
    if (my_putchar('0' + (n % 10)) != 0)
        return 84;
    return 0;
}
