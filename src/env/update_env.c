/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** Environment insert/update helpers
*/
#include <stdlib.h>

#include "env.h"
#include "my_utils.h"

static char *create_env_entry(char const *key, char const *value)
{
    char const *safe_value = value ? value : "";
    int total_len = my_strlen(key) + 1 + my_strlen(safe_value) + 1;
    char *new_entry = malloc(total_len);

    if (!new_entry)
        return NULL;
    new_entry[0] = '\0';
    my_strcpy(new_entry, key);
    my_strcat(new_entry, "=");
    my_strcat(new_entry, safe_value);
    return new_entry;
}

static char **replace_env_value(char **env, int index, char const *key,
    char const *value)
{
    char *new_entry = create_env_entry(key, value);

    if (!new_entry)
        return env;
    free(env[index]);
    env[index] = new_entry;
    return env;
}

static char **add_env_entry(char **env, char const *key, char const *value)
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

char **update_env(char **env, char const *key, char const *value)
{
    int index = find_env_index(env, key);

    if (index != -1)
        return replace_env_value(env, index, key, value);
    else
        return add_env_entry(env, key, value);
}
