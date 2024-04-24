NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude -Ilibft -g
SRCS = src/main.c \
	   src/ast.c \
	   src/ast_parse.c \
	   src/ast_redir.c \
	   src/ast_test.c \
	   src/data.c \
	   src/error.c \
	   src/env_var.c \
	   src/exec.c \
	   src/exec_pipe.c \
	   src/exec_redirs.c \
	   src/expand_string.c \
	   src/path.c \
	   src/utils.c \
	   src/builtins/cd.c \
	   src/builtins/echo.c \
	   src/builtins/export.c \
	   src/builtins/exit.c \
	   src/builtins/pwd.c \
	   src/builtins/unset.c \
	   src/builtins/utils.c \
	   src/get_next_line.c \
	   src/structures/buffer.c \
	   src/structures/buffer2.c \
	   src/structures/string.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

libft.a:
	make -C libft
	mv libft/libft.a libft.a

$(NAME): libft.a $(OBJS)
	$(CC) $^ -o $(NAME) -lreadline -L. -lft -g

clean:
	make -C libft clean
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME) libft.a

re: fclean all
