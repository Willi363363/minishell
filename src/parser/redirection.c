/*
** EPITECH PROJECT, 2026
** G-PSU-200-MPL-2-1-minishell2-15
** File description:
** redirection
*/

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "parser.h"
#include "my_utils.h"

static int write_heredoc_lines(const char *delim, int write_fd)
{
    char *line = NULL;
    size_t cap = 0;
    ssize_t read_len = 0;

    while (1) {
        read_len = getline(&line, &cap, stdin);
        if (read_len == -1)
            break;
        if (line && read_len > 0 && line[read_len - 1] == '\n')
            line[read_len - 1] = '\0';
        if (my_strcmp(line, delim) == 0)
            break;
        write(write_fd, line, my_strlen(line));
        write(write_fd, "\n", 1);
    }
    free(line);
    return SUCCESS;
}

static int open_heredoc(const char *delim)
{
    int pipes[2];

    if (pipe(pipes) == -1)
        return ERROR;
    if (write_heredoc_lines(delim, pipes[1]) == ERROR) {
        close(pipes[0]);
        close(pipes[1]);
        return ERROR;
    }
    close(pipes[1]);
    return pipes[0];
}

static int open_redir_fd(redir_t *redir)
{
    int flags = O_RDONLY;

    if (redir->type == REDIR_OUT)
        flags = O_CREAT | O_WRONLY | O_TRUNC;
    if (redir->type == REDIR_APPEND)
        flags = O_CREAT | O_WRONLY | O_APPEND;
    if (redir->type == REDIR_IN)
        return open(redir->target, O_RDONLY);
    if (redir->type == REDIR_HEREDOC)
        return open_heredoc(redir->target);
    return open(redir->target, flags, 0644);
}

static int dup_redir(redir_t *redir, int fd)
{
    if (redir->type == REDIR_IN || redir->type == REDIR_HEREDOC)
        return dup2(fd, STDIN_FILENO) == -1 ? ERROR : SUCCESS;
    return dup2(fd, STDOUT_FILENO) == -1 ? ERROR : SUCCESS;
}

static int apply_redir_one(redir_t *redir)
{
    int fd = -1;

    if (!redir || !redir->target)
        return SUCCESS;
    fd = open_redir_fd(redir);
    if (fd == -1)
        return ERROR;
    if (dup_redir(redir, fd) == ERROR)
        return ERROR;
    close(fd);
    return SUCCESS;
}

int apply_redirections(redir_t *redir)
{
    while (redir) {
        if (apply_redir_one(redir) == ERROR)
            return ERROR;
        redir = redir->next;
    }
    return SUCCESS;
}
