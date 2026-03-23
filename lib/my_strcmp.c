/*
** EPITECH PROJECT, 2025
** my_strcmp
** File description:
** Compares two strings
*/
#include "my_utils.h"

int my_strcmp(char const *s1, char const *s2)
{
    int i = 0;

    while (s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    return s1[i] - s2[i];
}
