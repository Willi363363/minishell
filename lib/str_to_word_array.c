/*
** EPITECH PROJECT, 2026
** str_to_word_array
** File description:
** str_to_word_array
*/

#include <stdlib.h>

#include "my_utils.h"

static int is_delimiter(char c, char delim)
{
    return (c == delim || (delim == ' ' && c == '\t'));
}

static int count_words(char const *str, char delim)
{
    int count = 0;
    int in_word = 0;

    if (str == NULL || str[0] == '\0')
        return (0);
    for (int i = 0; str[i]; i++) {
        if (is_delimiter(str[i], delim)) {
            in_word = 0;
            continue;
        }
        if (!in_word) {
            count++;
            in_word = 1;
        }
    }
    return (count);
}

static int update_word_count(int in_word, int count)
{
    if (in_word)
        return (count + 1);
    return (count);
}

static int find_word_start(char const *str, int word_nb, char delim)
{
    int count = 0;
    int in_word = 0;

    for (int i = 0; str[i]; i++) {
        if (is_delimiter(str[i], delim)) {
            count = update_word_count(in_word, count);
            in_word = 0;
            continue;
        }
        if (!in_word && count == word_nb)
            return (i);
        in_word = 1;
    }
    return (0);
}

static int get_word_length(char const *str, int start, char delim)
{
    int len = 0;

    while (str[start + len] && !is_delimiter(str[start + len], delim))
        len++;
    return (len);
}

static char *extract_word(char const *str, int word_nb, char delim)
{
    int start = find_word_start(str, word_nb, delim);
    int len = get_word_length(str, start, delim);
    char *word = malloc(sizeof(char) * (len + 1));

    if (word == NULL)
        return (NULL);
    word[len] = '\0';
    for (int i = 0; i < len; i++)
        word[i] = str[start + i];
    return (word);
}

static void free_array(char **array, int count)
{
    if (array == NULL)
        return;
    for (int i = 0; i < count; i++) {
        if (array[i] != NULL)
            free(array[i]);
    }
    free(array);
}

char **str_to_word_array(char const *str, char delim)
{
    int nb = count_words(str, delim);
    char **res = NULL;

    if (str == NULL)
        return (NULL);
    res = malloc(sizeof(char *) * (nb + 1));
    if (res == NULL)
        return (NULL);
    for (int i = 0; i < nb; i++) {
        res[i] = extract_word(str, i, delim);
        if (res[i] == NULL) {
            free_array(res, i);
            return (NULL);
        }
    }
    res[nb] = NULL;
    return (res);
}
