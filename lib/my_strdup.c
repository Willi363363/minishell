/*
** EPITECH PROJECT, 2025
** my_strdup
** File description:
** Duplicates a string
*/

#include <stdlib.h>

#include "my_utils.h"

char *my_strdup(char *str)
{
    char *copy;

    if (!str)
        return NULL;
    copy = malloc(sizeof(char) * (my_strlen(str) + 1));
    if (!copy)
        return NULL;
    my_strcpy(copy, str);
    return copy;
}
