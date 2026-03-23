/*
** EPITECH PROJECT, 2026
** G-PSU-200-MPL-2-1-minishell2-15
** File description:
** ast
*/

#include <stdlib.h>

#include "parser.h"
#include "my_utils.h"

static void free_redirs(redir_t *redir)
{
    redir_t *next = NULL;

    while (redir) {
        next = redir->next;
        if (redir->target)
            free(redir->target);
        free(redir);
        redir = next;
    }
}

static void free_command(ast_command_t *cmd)
{
    size_t i = 0;

    if (!cmd)
        return;
    if (cmd->argv) {
        while (cmd->argv[i]) {
            free(cmd->argv[i]);
            i++;
        }
        free(cmd->argv);
    }
    free_redirs(cmd->redirs);
    free(cmd);
}

void ast_destroy(ast_t *ast)
{
    if (!ast)
        return;
    ast_destroy(ast->left);
    ast_destroy(ast->right);
    free_command(ast->command);
    free(ast);
}

ast_t *ast_command_node(ast_command_t *cmd)
{
    ast_t *node = malloc(sizeof(ast_t));

    if (!node)
        return NULL;
    node->type = AST_COMMAND;
    node->left = NULL;
    node->right = NULL;
    node->command = cmd;
    return node;
}

ast_t *ast_binary_node(ast_type_t type, ast_t *left, ast_t *right)
{
    ast_t *node = malloc(sizeof(ast_t));

    if (!node)
        return NULL;
    node->type = type;
    node->left = left;
    node->right = right;
    node->command = NULL;
    return node;
}
