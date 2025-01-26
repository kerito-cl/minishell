NAME = minishell
SRCS_DIR		:= src

SRCS := 		parse.c \
				tokenize.c \
				signal.c \
				utils.c \
				parse_utils.c \
				assign_node.c \
				efe.c \
				quote_handler.c \
				create_cmd.c \
				main.c 

OFILES = $(SRCS:.c=.o)
CC = cc
FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OFILES)
	$(CC) $(FLAGS) $(OFILES) -o $(NAME) -lreadline

%.o: %.c
	$(CC) $(FLAGS) -c $< -I. -o $@

clean:
	rm -f $(OFILES)
fclean: clean
	rm -f $(NAME)
re: fclean all

.PHONY: all, clean, fclean, re

.PHONY: all clean fclean re run