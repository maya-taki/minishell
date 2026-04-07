NAME			= minishell
CC				= cc
CFLAGS			= -Werror -Wextra -Wall -g

LIBFT_DIR		= libft
LIBFT			= $(LIBFT_DIR)/libft.a
LIB_FLAGS		= -L$(LIBFT_DIR) -lft -lreadline

OBJ_DIR			= build
INCLUDE_DIRS	= includes $(LIBFT_DIR)/includes
INCLUDES		= $(foreach dir,$(INCLUDE_DIRS), -I$(dir))

GREEN 		:= \033[0;32m
YELLOW		:= \033[0;33m
RED			:= \033[0;31m
BLUE		:= \033[0;34m
RESET		:= \033[0m

0,




all: $(NAME)

fclean: $