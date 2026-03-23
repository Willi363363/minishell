/*
** EPITECH PROJECT, 2025
** my_strcat
** File description:
** Concatenates two strings
*/
#include <stddef.h>
#include <stdlib.h>

#include "my_utils.h"

static char *fill_and_rev(char *str, int value, int index, int neg)
{
    while (value) {
        str[index] = (value % 10) + '0';
        value = value / 10;
        index++;
    }
    if (neg)
        str[index] = '-';
    str = my_revstr(str);
    return str;
}

char *my_int_to_str(int value)
{
    char *str = malloc(INT_LEN * sizeof(char));
    int index = 0;
    int neg = 0;

    if (!str)
        return NULL;
    for (unsigned long i = 0; i < (INT_LEN * sizeof(char)); i++)
        str[i] = '\0';
    if (value == 0)
        str[0] = '0';
    if (value < 0) {
        neg = 1;
        value = -value;
    }
    return fill_and_rev(str, value, index, neg);
}
