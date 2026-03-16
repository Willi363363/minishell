/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** Environment insert/update helpers
*/
#include "my.h"

int find_env_index(char **env, char *key)
{
    int i = 0;
    int key_len = my_strlen(key);

    while (env[i]) {
        if (my_strncmp(env[i], key, key_len) == 0 && env[i][key_len] == '=')
            return i;
        i++;
    }
    return -1;
}

static char *create_env_entry(char *key, char *value)
{
    int total_len = my_strlen(key) + 1 + my_strlen(value) + 1;
    char *new_entry = malloc(total_len);

    if (!new_entry)
        return NULL;
    my_strcpy(new_entry, key);
    my_strcat(new_entry, "=");
    my_strcat(new_entry, value);
    return new_entry;
}

static char **replace_env_value(char **env, int index, char *key, char *value)
{
    char *new_entry = create_env_entry(key, value);

    if (!new_entry)
        return env;
    free(env[index]);
    env[index] = new_entry;
    return env;
}

int count_env(char **env)
{
    int count = 0;

    while (env[count])
        count++;
    return count;
}

static char **add_env_entry(char **env, char *key, char *value)
{
    int count = count_env(env);
    char **new_env = malloc(sizeof(char *) * (count + 2));
    int i = 0;

    if (!new_env)
        return env;
    while (i < count) {
        new_env[i] = env[i];
        i++;
    }
    new_env[i] = create_env_entry(key, value);
    if (!new_env[i]) {
        free(new_env);
        return env;
    }
    new_env[i + 1] = NULL;
    free(env);
    return new_env;
}

static int copy_without_index(char **new_env, char **env, int count, int index)
{
    int pos = 0;

    for (int i = 0; i < count; i++) {
        if (i == index)
            free(env[i]);
        else {
            new_env[pos] = env[i];
            pos++;
        }
    }
    new_env[pos] = NULL;
    return pos;
}

char **remove_env_key(char **env, char *key)
{
    int index = find_env_index(env, key);
    int count = count_env(env);
    char **new_env = NULL;

    if (index == -1)
        return env;
    new_env = malloc(sizeof(char *) * count);
    if (!new_env)
        return env;
    copy_without_index(new_env, env, count, index);
    free(env);
    return new_env;
}

char **update_env(char **env, char *key, char *value)
{
    int index = find_env_index(env, key);

    if (index != -1)
        return replace_env_value(env, index, key, value);
    else
        return add_env_entry(env, key, value);
}
