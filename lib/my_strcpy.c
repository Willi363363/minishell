/*
** EPITECH PROJECT, 2025
** my_strcpy
** File description:
** Copies a string into another
*/
#include "my_utils.h"

char *my_strcpy(char *dest, char const *src)
{
    int i = 0;

    for (; src[i] != '\0'; i++)
        dest[i] = src[i];
    dest[i] = '\0';
    return dest;
}
