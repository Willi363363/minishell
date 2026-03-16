/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** Builtin dispatch and external command execution entry
*/
#include "my.h"

static int put_on_fd(int fd, const char *str)
{
    if (write(fd, str, my_strlen(str)) == -1)
        return 84;
    return 0;
}

static void free_array(char **array)
{
    for (int i = 0; array[i]; i++)
        free(array[i]);
    free(array);
}

static int setenv_name_error(char *message)
{
    if (put_on_fd(2, message) == 84)
        return 84;
    return 1;
}

static int print_env(char **env)
{
    for (int i = 0; env[i]; i++) {
        if (put_on_fd(1, env[i]) == 84 || put_on_fd(1, "\n") == 84)
            return 84;
    }
    return 0;
}

static int validate_setenv_name(char *name)
{
    int i = 0;

    if (!name || !((name[0] >= 'A' && name[0] <= 'Z')
            || (name[0] >= 'a' && name[0] <= 'z')))
        return setenv_name_error(
            "setenv: Variable name must begin with a letter.\n");
    while (name[i]) {
        if (!((name[i] >= 'A' && name[i] <= 'Z')
                || (name[i] >= 'a' && name[i] <= 'z')
                || (name[i] >= '0' && name[i] <= '9')))
            return setenv_name_error(
                "setenv: Variable name must contain alphanumeric "
                "characters.\n");
        i++;
    }
    return 0;
}

static int modify_env(char ***env, char **array)
{
    int argc = 0;
    int valid = 0;

    while (array[argc])
        argc++;
    if (argc == 1)
        return print_env(*env);
    if (argc > 3) {
        if (put_on_fd(2, "setenv: Too many arguments.\n") == 84)
            return 84;
        return 1;
    }
    valid = validate_setenv_name(array[1]);
    if (valid != 0)
        return valid;
    *env = update_env(*env, array[1], array[2] ? array[2] : "");
    return 0;
}

static int handle_env_builtin(char **array, char **env)
{
    if (array[1]) {
        if (put_on_fd(2, "env: Too many arguments.\n") == 84)
            return 84;
        return 1;
    }
    return print_env(env);
}

static int handle_exec_status(int value, char *command)
{
    if (value == 127) {
        if (put_on_fd(2, command) == 84
            || put_on_fd(2, ": Command not found.\n") == 84)
            return 84;
        return 1;
    }
    if (value == 126) {
        if (put_on_fd(2, command) == 84
            || put_on_fd(2, ": Permission denied.\n") == 84)
            return 84;
        return 1;
    }
    return value;
}

static int run_builtin(char **array, char ***env, int value, int *handled)
{
    *handled = 1;
    if (my_strcmp(array[0], "cd") == 0)
        return cd_command(array, env, value);
    if (my_strcmp(array[0], "setenv") == 0)
        return modify_env(env, array);
    if (my_strcmp(array[0], "unsetenv") == 0)
        return my_unsetenv(env, array);
    if (my_strcmp(array[0], "env") == 0)
        return handle_env_builtin(array, *env);
    *handled = 0;
    return value;
}

int my_exec(char *buffer, char ***env, int code)
{
    char **array = NULL;
    int handled = 0;
    int value = 0;

    array = str_to_word_array(buffer, ' ');
    if (!env || !*env || !array)
        return 84;
    if (!array[0]) {
        free(array);
        return code;
    }
    value = run_builtin(array, env, value, &handled);
    if (!handled) {
        array = get_command_code(array, code);
        value = fork_process(array, *env);
        value = handle_exec_status(value, array[0]);
    }
    free_array(array);
    return value;
}
