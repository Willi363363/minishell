/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** unsetenv builtin implementation
*/
#include "my.h"

static int put_err(const char *str)
{
    if (write(2, str, my_strlen(str)) == -1)
        return 84;
    return 0;
}

static char **unset_function(char **env, char *key, int pos)
{
    int index = find_env_index(env, key);
    int count = count_env(env);
    char **new_env = malloc(sizeof(char *) * count);

    if (!new_env)
        return env;
    if (index == -1) {
        free(new_env);
        return env;
    }
    for (int i = 0; i < count; i++) {
        if (index != i) {
            new_env[pos] = env[i];
            pos++;
        } else
            free(env[i]);
    }
    new_env[pos] = NULL;
    free(env);
    return new_env;
}

static int unset_one_key(char ***env, char *key, int pos)
{
    if (my_strcmp(key, "*") == 0)
        return put_err("unsetenv: Wildcards not allowed.\n");
    *env = unset_function(*env, key, pos);
    return 0;
}

int my_unsetenv(char ***env, char **array)
{
    int pos = 0;
    int i = 1;
    int status = 0;

    if (!array[1]) {
        if (put_err("unsetenv: Too few arguments.\n") == 84)
            return 84;
        return 1;
    }
    while (array[i]) {
        status = unset_one_key(env, array[i], pos);
        if (status == 84)
            return 84;
        if (status != 0)
            return 1;
        i++;
    }
    return 0;
}
