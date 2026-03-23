/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** Fork, exec and child status handling
*/
#include <errno.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "loop.h"
#include "my_utils.h"

static int print_signal(int sig, int core)
{
    if (write(2, strsignal(sig), my_strlen(strsignal(sig))) == -1)
        return ERROR;
    if (core && write(2, " (core dumped)", 14) == -1)
        return ERROR;
    if (write(2, "\n", 1) == -1)
        return ERROR;
    return 128 + sig;
}

static int check_status(int status)
{
    int sig = SUCCESS;
    int exit_code = SUCCESS;

    if (WIFEXITED(status)) {
        exit_code = WEXITSTATUS(status);
        return exit_code;
    } else if (WIFSIGNALED(status)) {
        sig = WTERMSIG(status);
        return print_signal(sig, WCOREDUMP(status));
    }
    return SUCCESS;
}

static char *build_full_path(char *dir, char *command)
{
    int len = my_strlen(dir) + my_strlen(command) + 2;
    char *path = malloc(sizeof(char) * len);

    if (!path)
        return NULL;
    path[0] = '\0';
    my_strcpy(path, dir);
    my_strcat(path, "/");
    my_strcat(path, command);
    return path;
}

static void free_paths(char **paths)
{
    int i = 0;

    while (paths[i]) {
        free(paths[i]);
        i++;
    }
    free(paths);
}

static int exec_path_candidate(char *path, char **array, char **env)
{
    char *full_path = build_full_path(path, array[0]);

    if (!full_path)
        return ERROR;
    execve(full_path, array, env);
    free(full_path);
    if (errno == ENOENT || errno == ENOTDIR)
        return ERROR;
    return 126;
}

static int search_path(char **paths, char **array, char **env)
{
    int i = 0;
    int status = 0;

    while (paths[i]) {
        status = exec_path_candidate(paths[i], array, env);
        if (status == 126) {
            free_paths(paths);
            return 126;
        }
        i++;
    }
    free_paths(paths);
    return 127;
}

static int try_exec_with_path(char **array, char **env)
{
    char *path_var = NULL;
    char **paths = NULL;
    int i = 0;
    int len = 4;

    while (env[i]) {
        if (my_strncmp(env[i], "PATH", len) == 0 && env[i][len] == '=')
            path_var = env[i] + len + 1;
        i++;
    }
    if (!path_var || path_var[0] == '\0')
        return 127;
    paths = str_to_word_array(path_var, ':');
    if (!paths)
        return 127;
    return search_path(paths, array, env);
}

static int execute_child(char **array, char **env)
{
    int i = 0;

    while (array[0][i] && array[0][i] != '/')
        i++;
    if (array[0][i] == '/') {
        execve(array[0], array, env);
        if (errno == ENOENT || errno == ENOTDIR || errno == ENOEXEC)
            return 127;
        return 126;
    }
    return try_exec_with_path(array, env);
}

static int manage_process(char **array, char **env, pid_t pid)
{
    int status = 0;
    int child_status = 0;

    if (pid == 0) {
        child_status = execute_child(array, env);
        exit(child_status);
    }
    if (waitpid(pid, &status, 0) == -1) {
        return ERROR;
    }
    return check_status(status);
}

int fork_process(char **array, char **env)
{
    pid_t pid;

    pid = fork();
    if (pid == -1)
        return ERROR;
    return manage_process(array, env, pid);
}
