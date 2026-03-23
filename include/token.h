/*
** EPITECH PROJECT, 2026
** G-PSU-200-MPL-2-1-minishell2-15
** File description:
** token
*/

#ifndef TOKEN_H_
    #define TOKEN_H_

    #include <stddef.h>

typedef enum token_type_e {
    TOK_ARGS,
    TOK_SEMICOLON,
    TOK_PIPE,
    TOK_LESS_THAN,
    TOK_GREATER_THAN,
    TOK_DOUBLE_LESS_THAN,
    TOK_DOUBLE_GREATER_THAN,
    TOK_EOF,
} token_type_t;

typedef struct token_s {
    token_type_t type;
    char *value;
    struct token_s *next;
} token_t;

token_t *token_create(token_type_t type, const char *value, size_t len);
void token_destroy(token_t *token);

#endif /* !TOKEN_H_ */
