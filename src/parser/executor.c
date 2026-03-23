/*
** EPITECH PROJECT, 2026
** G-PSU-200-MPL-2-1-minishell2-15
** File description:
** executor
*/

#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "parser.h"
#include "loop.h"
#include "my_utils.h"

static int wait_child(pid_t pid)
{
    int status = 0;

    if (waitpid(pid, &status, 0) == -1)
        return ERROR;
    if (WIFEXITED(status))
        return WEXITSTATUS(status);
    if (WIFSIGNALED(status))
        return 128 + WTERMSIG(status);
    return SUCCESS;
}

static int exec_command_child(shell_t *shell, ast_command_t *cmd, int input_fd)
{
    if (input_fd != -1 && dup2(input_fd, STDIN_FILENO) == -1)
        return ERROR;
    if (apply_redirections(cmd->redirs) == ERROR)
        return ERROR;
    return exec_command(shell, cmd->argv);
}

static int exec_command_node(shell_t *shell, ast_command_t *cmd, int input_fd,
    int in_pipeline)
{
    pid_t pid = 0;
    int status = 0;

    if (!cmd || !cmd->argv || !cmd->argv[0])
        return shell ? shell->last_status : ERROR;
    if (!in_pipeline && !cmd->redirs)
        return exec_command(shell, cmd->argv);
    pid = fork();
    if (pid == -1)
        return ERROR;
    if (pid == 0) {
        status = exec_command_child(shell, cmd, input_fd);
        exit(status == ERROR ? 1 : status);
    }
    if (input_fd != -1)
        close(input_fd);
    return wait_child(pid);
}

static pid_t launch_left_child(shell_t *shell, ast_t *left, int *fds)
{
    pid_t pid = fork();
    int status = 0;

    if (pid == -1)
        return -1;
    if (pid == 0) {
        close(fds[0]);
        if (dup2(fds[1], STDOUT_FILENO) == -1)
            exit(1);
        status = exec_ast(shell, left);
        exit(status == ERROR ? 1 : status);
    }
    return pid;
}

static int exec_pipeline(shell_t *shell, ast_t *node, int input_fd)
{
    int fds[2];
    pid_t left_pid = 0;
    int status = 0;

    if (node->type != AST_PIPE)
        return exec_command_node(shell, node->command, input_fd, 0);
    if (pipe(fds) == -1)
        return ERROR;
    left_pid = launch_left_child(shell, node->left, fds);
    if (left_pid == -1)
        return ERROR;
    close(fds[1]);
    if (input_fd != -1)
        close(input_fd);
    status = (node->right->type == AST_PIPE)
        ? exec_pipeline(shell, node->right, fds[0])
        : exec_command_node(shell, node->right->command, fds[0], 1);
    wait_child(left_pid);
    return status;
}

int exec_ast(shell_t *shell, ast_t *ast)
{
    int status = SUCCESS;

    if (!ast)
        return ERROR;
    if (ast->type == AST_SEQUENCE) {
        status = exec_ast(shell, ast->left);
        if (status == ERROR)
            return ERROR;
        return exec_ast(shell, ast->right);
    }
    if (ast->type == AST_PIPE) {
        status = exec_pipeline(shell, ast, -1);
        if (status != ERROR && shell)
            shell->last_status = status;
        return status;
    }
    status = exec_command_node(shell, ast->command, -1, 0);
    if (status != ERROR && shell)
        shell->last_status = status;
    return status;
}
