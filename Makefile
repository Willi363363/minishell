#
## EPITECH PROJECT, 2025
## Makefile
## File description:
## Create a makefile
##

NAME = mysh

CC	=	epiclang
CFLAGS = -W -Wall -Wextra -Iinclude

SRC 	= 	src/main.c \
		src/cd_command.c \
		src/change_directory.c \
		src/dup_env.c \
		src/fork_process.c \
		src/get_command_code.c \
		src/init_shell_env.c \
		src/loop_terminal.c \
		src/my_exec.c \
		src/unsetenv.c \
		src/update_env.c \
		lib/my_put_nbr.c \
		lib/my_putchar.c \
		lib/my_putstr.c \
		lib/my_strcat.c \
		lib/my_strcmp.c \
		lib/my_strncmp.c \
		lib/my_strcpy.c \
		lib/my_strdup.c \
		lib/my_strlen.c \
		lib/my_revstr.c \
		lib/my_int_to_str.c \
		lib/str_to_word_array.c

OBJ = 	$(SRC:.c=.o)

all:	$(NAME)

$(NAME): $(OBJ)
	$(CC) -o $@ $(OBJ)

clean:
	$(RM) $(OBJ)

fclean:		clean
	$(RM) $(NAME)

re:		fclean all

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

.PHONY: all clean fclean re