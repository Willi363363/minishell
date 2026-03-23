/*
** EPITECH PROJECT, 2026
** G-PSU-200-MPL-2-1-minishell2-15
** File description:
** put_on_fd
*/

#include <unistd.h>

#include "my_utils.h"

int put_on_fd(int fd, const char *str)
{
    if (write(fd, str, my_strlen(str)) == -1)
        return 84;
    return 0;
}
