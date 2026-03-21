##
## EPITECH PROJECT, 2026
## Makefile
## File description:
## Makefile for minishell project
#

CFLAGS = -Iinclude -W -Wall -Werror -Wextra -g
LDFLAGS = -g

NAME = mysh

CC = epiclang

SRC = $(shell find src -name '*.c')
LIB_SRC = $(shell find lib -name '*.c')
OBJ = $(SRC:.c=.o) $(LIB_SRC:.c=.o)

TESTS = unit_tests
TESTS_SRC = $(shell find tests -name '*.c')
TESTS_LDFLAGS = -lcriterion --coverage

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

clean:
	$(RM) $(OBJ) *.gcno *.gcda *.gcov

fclean: clean
	$(RM) $(NAME) $(TESTS)

re: fclean all

$(TESTS): $(NAME)
	$(CC) $(CFLAGS) $(TESTS_LDFLAGS) $(TESTS_SRC) $(SRC) $(LIB_SRC) -o $@

tests_run: $(TESTS)
	./$(TESTS)

tests_re: clean tests_run

.PHONY: all clean fclean re
