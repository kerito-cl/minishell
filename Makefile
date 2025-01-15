# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/15 07:44:51 by ipersids          #+#    #+#              #
#    Updated: 2025/01/15 08:33:02 by ipersids         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program name
NAME			:= minishell

# Submodule libft
SUBM_LIBFT_DIR	:= libft
SUBM_LIBFT_LIB	:= $(SUBM_LIBFT_DIR)/libft.a
SUBM_LIBFT_HDR	:= -I$(SUBM_LIBFT_DIR)/include

# Compilation variables
CC				:= clang
CFLAGS			:= -Wall -Wextra -Werror
HDRS			:= -Iinclude $(SUBM_LIBFT_HDR)
LIBS			:= -L$(SUBM_LIBFT_DIR) -lft

# macOS specific flags
ifeq ($(shell uname -s),Darwin)
    HDRS += -I/opt/homebrew/opt/readline/include
    LIBS += -L/opt/homebrew/opt/readline/lib -lreadline
else
	LIBS += -lreadline
endif

# Directories
SRCS_DIR		:= src
OBJ_DIR			:= obj

# Sources and objects
SRCS			:= $(SRCS_DIR)/signals/sig_handler.c \
        		   $(SRCS_DIR)/signals/sig_sigaction_init.c
SRC_MAIN		:= $(SRCS_DIR)/main.c

OBJS			:= $(SRCS:$(SRCS_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJ_MAIN		:= $(SRC_MAIN:$(SRCS_DIR)/%.c=$(OBJ_DIR)/%.o)

# RULES
all: update-submodule build-submodule $(OBJ_DIR) $(NAME)

# Rule to create the obj/* directory
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)/signals

# Rule for creating object files
$(OBJ_DIR)/%.o: $(SRCS_DIR)/%.c
	$(CC) $(CFLAGS) $(HDRS) -c $< -o $@

# Linking rule
$(NAME): $(OBJS) $(OBJ_MAIN)
	$(CC) $(CFLAGS) $(OBJS) $(OBJ_MAIN) $(HDRS) $(LIBS) -o $(NAME)

# Update submodule libft --init
update-submodule:
	@git submodule init
	@git submodule update --recursive

# Build submodule libft
build-submodule:
	@$(MAKE) -C $(SUBM_LIBFT_DIR) 

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(SUBM_LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME) $(SUBM_LIBFT_LIB)

re: fclean all

run: all
	@echo "\n\033[036m\tWELCOME TO MINISHELL:\033[0m\n"
	@./minishell

.PHONY: all clean fclean re run