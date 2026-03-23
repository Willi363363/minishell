/*
** EPITECH PROJECT, 2026
** G-PSU-200-MPL-2-1-minishell2-15
** File description:
** parser_utils
*/

#include <stdlib.h>

#include "parser.h"
#include "my_utils.h"

char *parser_dup_slice(const char *start, size_t len)
{
    char *out = NULL;
    size_t i = 0;

    out = malloc(sizeof(char) * (len + 1));
    if (!out)
        return NULL;
    while (i < len) {
        out[i] = start[i];
        i++;
    }
    out[len] = '\0';
    return out;
}

redir_type_t parser_map_redir(token_type_t type)
{
    if (type == TOK_LESS_THAN)
        return REDIR_IN;
    if (type == TOK_GREATER_THAN)
        return REDIR_OUT;
    if (type == TOK_DOUBLE_GREATER_THAN)
        return REDIR_APPEND;
    return REDIR_HEREDOC;
}

redir_t *parser_add_redir(redir_t *head, token_t *target, token_type_t type)
{
    redir_t *node = malloc(sizeof(redir_t));

    if (!node || !target || !target->value)
        return NULL;
    node->target = parser_dup_slice(target->value, my_strlen(target->value));
    if (!node->target) {
        free(node);
        return NULL;
    }
    node->type = parser_map_redir(type);
    node->next = head;
    return node;
}

int parser_is_redir(token_type_t type)
{
    return (type == TOK_LESS_THAN || type == TOK_GREATER_THAN
        || type == TOK_DOUBLE_GREATER_THAN || type == TOK_DOUBLE_LESS_THAN);
}

ast_command_t *parser_alloc_command(size_t argc)
{
    ast_command_t *cmd = malloc(sizeof(ast_command_t));

    if (!cmd)
        return NULL;
    cmd->redirs = NULL;
    cmd->argv = malloc(sizeof(char *) * (argc + 1));
    if (!cmd->argv) {
        free(cmd);
        return NULL;
    }
    return cmd;
}
