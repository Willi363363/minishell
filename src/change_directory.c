/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** Implementation of cd path switching and PWD/OLDPWD updates
*/
#include "my.h"

static int put_on_fd(int fd, const char *str)
{
    if (write(fd, str, my_strlen(str)) == -1)
        return 84;
    return 0;
}

static int put_cd_errno(char *path)
{
    if (put_on_fd(2, path) == 84)
        return 84;
    if (put_on_fd(2, ": ") == 84)
        return 84;
    if (put_on_fd(2, strerror(errno)) == 84)
        return 84;
    if (put_on_fd(2, ".\n") == 84)
        return 84;
    return 1;
}

static char *find_env_value(char **env, char *name)
{
    int i = 0;
    int len = my_strlen(name);

    while (env[i]) {
        if (my_strncmp(env[i], name, len) == 0 && env[i][len] == '=')
            return env[i] + len + 1;
        i++;
    }
    return NULL;
}

static int update_pwd(char ***env, char *old_path)
{
    char *new_path = NULL;

    if (old_path) {
        *env = update_env(*env, "OLDPWD", old_path);
        free(old_path);
    }
    new_path = getcwd(NULL, 0);
    if (new_path) {
        *env = update_env(*env, "PWD", new_path);
        free(new_path);
    }
    return 0;
}

static int cd_home(char ***env, char *home)
{
    char *old_path = NULL;

    if (!home) {
        if (put_on_fd(2, "cd: HOME not set.\n") == 84)
            return 84;
        return 1;
    }
    old_path = getcwd(NULL, 0);
    if (chdir(home) != 0) {
        free(old_path);
        return put_cd_errno(home);
    }
    return update_pwd(env, old_path);
}

static int cd_oldpwd(char ***env, char *old)
{
    char *old_path = NULL;

    if (!old) {
        if (put_on_fd(2, ": No such file or directory.\n") == 84)
            return 84;
        return 1;
    }
    old_path = getcwd(NULL, 0);
    if (chdir(old) != 0) {
        free(old_path);
        return put_cd_errno(old);
    }
    return update_pwd(env, old_path);
}

static int cd_to_path(char ***env, char *path)
{
    char *old_path = getcwd(NULL, 0);

    if (chdir(path) != 0) {
        free(old_path);
        return put_cd_errno(path);
    }
    return update_pwd(env, old_path);
}

int change_directory(char **array, char ***env, char *home, char *old)
{
    int argc = 0;

    while (array[argc])
        argc++;
    home = find_env_value(*env, "HOME");
    old = find_env_value(*env, "OLDPWD");
    if (argc > 2) {
        if (put_on_fd(2, "cd: Too many arguments.\n") == 84)
            return 84;
        return 1;
    }
    if (argc == 1 || my_strcmp(array[1], "~") == 0)
        return cd_home(env, home);
    if (my_strcmp(array[1], "-") == 0)
        return cd_oldpwd(env, old);
    return cd_to_path(env, array[1]);
}
