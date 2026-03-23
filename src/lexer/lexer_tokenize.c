/*
** EPITECH PROJECT, 2026
** G-PSU-200-MPL-2-1-minishell2-15
** File description:
** lexer_tokenize
*/

#include "my_utils.h"
#include "lexer.h"
#include "token.h"
#include <stdlib.h>

static int is_whitespace(char c)
{
    return (c == ' ' || c == '\t' || c == '\n' ||
        c == '\r' || c == '\f' || c == '\v');
}

static int is_operator(char c)
{
    return (c == ';' || c == '|' || c == '<' || c == '>');
}

static token_t *find_tail(token_t *token)
{
    while (token && token->next)
        token = token->next;
    return token;
}

static int append_token(lexer_t *lexer, token_type_t type,
    const char *start, size_t len)
{
    token_t *new_token = NULL;
    token_t *tail = NULL;

    new_token = token_create(type, start, len);
    if (!new_token)
        return ERROR;
    if (!lexer->tokens)
        lexer->tokens = new_token;
    else {
        tail = find_tail(lexer->tokens);
        tail->next = new_token;
    }
    lexer->token_count++;
    return SUCCESS;
}

static token_type_t detect_operator(const char *input, size_t *consumed)
{
    if (input[0] == '<' && input[1] == '<') {
        *consumed = 2;
        return TOK_DOUBLE_LESS_THAN;
    }
    if (input[0] == '>' && input[1] == '>') {
        *consumed = 2;
        return TOK_DOUBLE_GREATER_THAN;
    }
    *consumed = 1;
    if (input[0] == ';')
        return TOK_SEMICOLON;
    if (input[0] == '|')
        return TOK_PIPE;
    if (input[0] == '<')
        return TOK_LESS_THAN;
    return TOK_GREATER_THAN;
}

static int handle_operator(lexer_t *lexer, const char *input, size_t *index)
{
    size_t op_len = 0;
    token_type_t op_type = TOK_ARGS;

    op_type = detect_operator(&input[*index], &op_len);
    if (append_token(lexer, op_type, &input[*index], op_len) == ERROR)
        return ERROR;
    *index += op_len;
    return SUCCESS;
}

static int handle_word(lexer_t *lexer, const char *input, size_t *index)
{
    size_t start = *index;

    while (input[*index] != '\0' && !is_whitespace(input[*index])
        && !is_operator(input[*index]))
        (*index)++;
    if (append_token(lexer, TOK_ARGS, &input[start], *index - start) == ERROR)
        return ERROR;
    return SUCCESS;
}

static void skip_whitespace(const char *input, size_t *index)
{
    while (input[*index] != '\0' && is_whitespace(input[*index]))
        (*index)++;
}

int lexer_tokenize(lexer_t *lexer, const char *input)
{
    size_t i = 0;
    int status = SUCCESS;

    if (!input || !lexer)
        return ERROR;
    while (input[i] != '\0') {
        skip_whitespace(input, &i);
        if (input[i] == '\0')
            break;
        status = is_operator(input[i])
            ? handle_operator(lexer, input, &i)
            : handle_word(lexer, input, &i);
        if (status == ERROR)
            return ERROR;
    }
    return append_token(lexer, TOK_EOF, "", 0);
}
