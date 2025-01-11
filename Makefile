NAME = minishell
PNAME = libftprintf.a
SOURCES = main.c ft_split.c utils.c children.c error.c
OFILES = $(SOURCES:.c=.o)
CC = cc
FLAGS = -Wall -Wextra -Werror
PSOURCES = ./printf/ft_printf.c ./printf/ft_putnbr_fd.c \
			 ./printf/ft_strlen.c ./printf/ft_strdup.c ./printf/ft_printhex.c
PFILES = $(PSOURCES:.c=.o)

all: $(PNAME) $(NAME)

$(PNAME): $(PFILES)
	ar -rcs $(PNAME) $(PFILES)

$(NAME): $(OFILES) $(PNAME)
	$(CC) $(FLAGS) $(OFILES) -o $(NAME) -lreadline -L. -lftprintf 

%.o: %.c
	$(CC) $(FLAGS) -c $< -I. -o $@

clean:
	rm -f $(OFILES) $(PFILES)
fclean: clean
	rm -f $(NAME) $(PNAME)
re: fclean all

.PHONY: all, clean, fclean, re
