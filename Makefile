# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/15 07:44:51 by ipersids          #+#    #+#              #
#    Updated: 2025/01/19 00:27:51 by ipersids         ###   ########.fr        #
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
        		   $(SRCS_DIR)/signals/sig_sigaction_init.c \
				   $(SRCS_DIR)/environment/env_init.c \
				   $(SRCS_DIR)/environment/env_free.c \
				   $(SRCS_DIR)/environment/env_find_variable.c \
				   $(SRCS_DIR)/environment/env_add.c \
				   $(SRCS_DIR)/environment/env_remove.c \
				   $(SRCS_DIR)/environment/env_find_value.c \
				   $(SRCS_DIR)/builtins/builtin_echo.c \
				   $(SRCS_DIR)/builtins/builtin_env.c \
				   $(SRCS_DIR)/builtins/builtin_export.c \
				   $(SRCS_DIR)/builtins/builtin_unset.c \
				   $(SRCS_DIR)/builtins/builtin_pwd.c \
				   $(SRCS_DIR)/builtins/builtin_exit.c \
				   $(SRCS_DIR)/builtins/utils/builtin_is_identifier_valid.c \
				   $(SRCS_DIR)/destructor/exit_destroy_minishell.c
				   
SRC_MAIN		:= $(SRCS_DIR)/main.c

OBJS			:= $(SRCS:$(SRCS_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJ_MAIN		:= $(SRC_MAIN:$(SRCS_DIR)/%.c=$(OBJ_DIR)/%.o)

# RULES
all: update-submodule build-submodule $(OBJ_DIR) $(NAME)

# Rule to create the obj/* directory
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/signals
	@mkdir -p $(OBJ_DIR)/environment
	@mkdir -p $(OBJ_DIR)/builtins
	@mkdir -p $(OBJ_DIR)/builtins/utils
	@mkdir -p $(OBJ_DIR)/destructor

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

# TESTING >>>
TEST_SRC		:= tests/test_main.c tests/test_env.c tests/test_builtin.c
TEST_OBJ		:= $(TEST_SRC:tests/%.c=tests/%.o)

test: update-submodule build-submodule $(OBJ_DIR) $(OBJS) $(TEST_OBJ)
	$(CC) $(CFLAGS) $(OBJS) $(TEST_OBJ) $(HDRS) $(LIBS) -o test_main

%.o: %.c
	$(CC) $(CFLAGS) $(HDRS) -c $< -o $@

tclean: clean
	@rm -f $(TEST_OBJ) test_main
# END OF TESTING <<<

.PHONY: all clean fclean re run