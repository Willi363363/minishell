/*
** EPITECH PROJECT, 2026
** G-PSU-200-MPL-2-1-minishell2-15
** File description:
** parser
*/

#ifndef PARSER_H_
    #define PARSER_H_

    #include "token.h"
    #include "shell.h"

typedef enum ast_type_e {
    AST_COMMAND,
    AST_SEQUENCE,
    AST_PIPE
} ast_type_t;

typedef enum redir_type_e {
    REDIR_IN,
    REDIR_OUT,
    REDIR_APPEND,
    REDIR_HEREDOC
} redir_type_t;

typedef struct redir_s {
    redir_type_t type;
    char *target;
    struct redir_s *next;
} redir_t;

typedef struct ast_command_s {
    char **argv;
    redir_t *redirs;
} ast_command_t;

typedef struct ast_s {
    ast_type_t type;
    struct ast_s *left;
    struct ast_s *right;
    ast_command_t *command;
} ast_t;

ast_t *parse_tokens(token_t *tokens);
void ast_destroy(ast_t *ast);
int exec_ast(shell_t *shell, ast_t *ast);
ast_t *ast_command_node(ast_command_t *cmd);
ast_t *ast_binary_node(ast_type_t type, ast_t *left, ast_t *right);
char *parser_dup_slice(const char *start, size_t len);
redir_t *parser_add_redir(redir_t *head, token_t *target, token_type_t type);
int parser_is_redir(token_type_t type);
ast_command_t *parser_alloc_command(size_t argc);
int apply_redirections(redir_t *redir);

#endif /* !PARSER_H_ */
