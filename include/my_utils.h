/*
** EPITECH PROJECT, 2026
** G-PSU-200-MPL-2-1-minishell2-15
** File description:
** utils
*/

#ifndef UTILS_H_
    #define UTILS_H_

    #define INT_LEN 12
    #define BIN_PATH "/bin/"
    #define SUCCESS 0
    #define ERROR 84

int my_put_nbr(int nb);
int my_putchar(char c);
int my_putstr(char const *str);
char *my_strcat(char *dest, char const *src);
int my_strcmp(char const *s1, char const *s2);
char *my_strcpy(char *dest, char const *src);
char *my_strdup(char *str);
int my_strlen(char const *str);
char **str_to_word_array(char const *str, char delim);
char *my_revstr(char *str);
char *my_int_to_str(int value);
int my_strncmp(char const *s1, char const *s2, int n);
int put_on_fd(int fd, const char *str);

#endif /* !UTILS_H_ */
