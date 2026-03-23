/*
** EPITECH PROJECT, 2025
** my_strcat
** File description:
** Concatenates two strings
*/
#include "my_utils.h"

char *my_revstr(char *str)
{
    int len = my_strlen(str) - 1;
    char temp;

    for (int i = 0; i <= len / 2; i++) {
        temp = str[i];
        str[i] = str[len - i];
        str[len - i] = temp;
    }
    return str;
}
