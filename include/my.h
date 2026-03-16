/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** Global includes, constants and function prototypes for mysh
*/

#ifndef MY
    #define MY
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <signal.h>
    #include <stdint.h>
    #include <sys/types.h>
    #include <sys/wait.h>
    #include <errno.h>
    #define INT_LEN 12
    #define BIN_PATH "/bin/"

int my_put_nbr(int nb);
int my_putchar(char c);
int my_putstr(char const *str);
char *my_strcat(char *dest, char const *src);
int my_strcmp(char *s1, char *s2);
char *my_strcpy(char *dest, char const *src);
char *my_strdup(char *str);
int my_strlen(char const *str);
char **str_to_word_array(char *str, char delim);
char *my_revstr(char *str);
char *my_int_to_str(int value);
int my_strncmp(char *s1, char *s2, int n);

char **dup_env(char **env);
char **update_env(char **env, char *key, char *value);
int fork_process(char **array, char **env);
int my_exec(char *buffer, char ***env, int code);
int loop_terminal(char ***env, int value, int input, size_t bufsize);
char **get_command_code(char **array, int code);
int change_directory(char **array, char ***env, char *home, char *old);
int cd_command(char **array, char ***env, int value);
char **get_command_code(char **array, int code);
int find_env_index(char **env, char *key);
int count_env(char **env);
int my_unsetenv(char ***env, char **array);
char **init_shell_env(char **env);
char **remove_env_key(char **env, char *key);

#endif /* MY */
