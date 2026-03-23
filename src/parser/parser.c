/*
** EPITECH PROJECT, 2026
** G-PSU-200-MPL-2-1-minishell2-15
** File description:
** parser
*/

#include <stdlib.h>

#include "parser.h"
#include "my_utils.h"

static void free_command_partial(ast_command_t *cmd, size_t filled)
{
    size_t i = 0;
    redir_t *next = NULL;

    if (!cmd)
        return;
    if (cmd->argv) {
        while (i < filled) {
            free(cmd->argv[i]);
            i++;
        }
        free(cmd->argv);
    }
    while (cmd->redirs) {
        next = cmd->redirs->next;
        if (cmd->redirs->target)
            free(cmd->redirs->target);
        free(cmd->redirs);
        cmd->redirs = next;
    }
    free(cmd);
}

static int handle_arg(ast_command_t *cmd, token_t *tok, size_t *idx)
{
    size_t len = 0;

    if (!tok || !cmd || !idx)
        return ERROR;
    len = my_strlen(tok->value);
    cmd->argv[*idx] = parser_dup_slice(tok->value, len);
    if (!cmd->argv[*idx])
        return ERROR;
    (*idx)++;
    return SUCCESS;
}

static int handle_redir(ast_command_t *cmd, token_t **tok, size_t filled)
{
    if (!cmd || !tok || !*tok || !(*tok)->next)
        return ERROR;
    cmd->redirs = parser_add_redir(cmd->redirs, (*tok)->next, (*tok)->type);
    if (!cmd->redirs) {
        free_command_partial(cmd, filled);
        return ERROR;
    }
    *tok = (*tok)->next;
    return SUCCESS;
}

static int parse_command_body(ast_command_t *cmd, token_t **tok, size_t *idx)
{
    while (*tok && (*tok)->type != TOK_PIPE && (*tok)->type != TOK_SEMICOLON
        && (*tok)->type != TOK_EOF) {
        if ((*tok)->type == TOK_ARGS && handle_arg(cmd, *tok, idx) == ERROR)
            return ERROR;
        if (parser_is_redir((*tok)->type)
            && handle_redir(cmd, tok, *idx) == ERROR)
            return ERROR;
        *tok = (*tok)->next;
    }
    return SUCCESS;
}

static size_t count_args(token_t *tok)
{
    size_t count = 0;
    token_type_t t;

    while (tok && tok->type != TOK_PIPE && tok->type != TOK_SEMICOLON
        && tok->type != TOK_EOF) {
        t = tok->type;
        if (t == TOK_ARGS)
            count++;
        if (t == TOK_LESS_THAN || t == TOK_GREATER_THAN
            || t == TOK_DOUBLE_GREATER_THAN || t == TOK_DOUBLE_LESS_THAN)
            tok = tok->next;
        tok = tok ? tok->next : NULL;
    }
    return count;
}

static ast_command_t *parse_command_node(token_t **tok)
{
    ast_command_t *cmd = NULL;
    size_t argc = 0;
    size_t idx = 0;

    if (!tok || !*tok)
        return NULL;
    argc = count_args(*tok);
    cmd = parser_alloc_command(argc);
    if (!cmd)
        return NULL;
    if (parse_command_body(cmd, tok, &idx) == ERROR) {
        free_command_partial(cmd, idx);
        return NULL;
    }
    cmd->argv[idx] = NULL;
    return cmd;
}

static ast_t *parse_simple(token_t **tok)
{
    ast_command_t *cmd = NULL;

    if (!tok || !*tok)
        return NULL;
    cmd = parse_command_node(tok);
    if (!cmd)
        return NULL;
    return ast_command_node(cmd);
}

static ast_t *parse_pipeline(token_t **tok)
{
    ast_t *left = NULL;
    ast_t *right = NULL;

    left = parse_simple(tok);
    if (!left)
        return NULL;
    while (*tok && (*tok)->type == TOK_PIPE) {
        *tok = (*tok)->next;
        right = parse_simple(tok);
        if (!right)
            return NULL;
        left = ast_binary_node(AST_PIPE, left, right);
        if (!left)
            return NULL;
    }
    return left;
}

static ast_t *parse_sequence(token_t **tok)
{
    ast_t *left = NULL;
    ast_t *right = NULL;

    left = parse_pipeline(tok);
    if (!left)
        return NULL;
    while (*tok && (*tok)->type == TOK_SEMICOLON) {
        *tok = (*tok)->next;
        right = parse_pipeline(tok);
        if (!right)
            return NULL;
        left = ast_binary_node(AST_SEQUENCE, left, right);
        if (!left)
            return NULL;
    }
    return left;
}

ast_t *parse_tokens(token_t *tokens)
{
    token_t *cursor = tokens;

    if (!tokens)
        return NULL;
    return parse_sequence(&cursor);
}
