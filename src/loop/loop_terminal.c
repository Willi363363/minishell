/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** Interactive/non-interactive read-execute loop
*/
#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#include "loop.h"
#include "my_utils.h"
#include "lexer.h"
#include "parser.h"

static int show_prompt(shell_t *shell)
{
    if (!shell || !shell->interactive)
        return SUCCESS;
    if (write(1, "$> ", 3) == -1)
        return ERROR;
    return SUCCESS;
}

static void trim_newline(char *buffer, ssize_t input)
{
    if (!buffer || input <= 0)
        return;
    if (buffer[input - 1] == '\n')
        buffer[input - 1] = '\0';
}

static int handle_read_failure(void)
{
    if (errno == EINTR)
        return 1;
    if (errno == 0)
        return SUCCESS;
    return ERROR;
}

static int process_read_result(ssize_t input)
{
    int failure = SUCCESS;

    if (input != -1)
        return 0;
    failure = handle_read_failure();
    if (failure == 1)
        return 1;
    if (failure == ERROR)
        return ERROR;
    return 2;
}

static int inspect_line(shell_t *shell, ssize_t input)
{
    if (!shell)
        return ERROR;
    trim_newline(shell->line, input);
    if (!shell->line || shell->line[0] == '\0')
        return 1;
    if (my_strcmp(shell->line, "exit") == 0)
        return 2;
    return 0;
}

static int cleanup_and_return(lexer_t *lexer, ast_t *ast, int code)
{
    if (ast)
        ast_destroy(ast);
    if (lexer)
        lexer_destroy(lexer);
    return code;
}

static int build_and_run_ast(shell_t *shell)
{
    lexer_t *lexer = lexer_create();
    ast_t *ast = NULL;
    int status = 0;

    if (!lexer)
        return ERROR;
    if (lexer_tokenize(lexer, shell->line) == ERROR)
        return cleanup_and_return(lexer, NULL, ERROR);
    ast = parse_tokens(lexer->tokens);
    if (!ast)
        return cleanup_and_return(lexer, NULL, ERROR);
    status = exec_ast(shell, ast);
    if (status == ERROR)
        return cleanup_and_return(lexer, ast, ERROR);
    shell->last_status = status;
    return cleanup_and_return(lexer, ast, SUCCESS);
}

static int handle_input(shell_t *shell, ssize_t input)
{
    int status = 0;

    if (!shell)
        return ERROR;
    status = process_read_result(input);
    if (status)
        return status;
    status = inspect_line(shell, input);
    if (status)
        return status;
    return build_and_run_ast(shell);
}

static int process_iteration(shell_t *shell)
{
    ssize_t input = 0;
    int prompt_status = 0;

    prompt_status = show_prompt(shell);
    if (prompt_status == ERROR)
        return ERROR;
    errno = 0;
    input = getline(&shell->line, &shell->line_cap, stdin);
    return handle_input(shell, input);
}

int shell_run(shell_t *shell)
{
    int status = SUCCESS;

    if (!shell)
        return ERROR;
    while (1) {
        status = process_iteration(shell);
        if (status == ERROR)
            return ERROR;
        if (status == 1)
            continue;
        if (status == 2)
            break;
    }
    return shell->last_status;
}
