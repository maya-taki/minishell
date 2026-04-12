NAME			= minishell
CC				= cc
CFLAGS			= -Werror -Wextra -Wall -g

LIBFT_DIR		= libft
LIBFT			= $(LIBFT_DIR)/libft.a
LIB_FLAGS		= -L$(LIBFT_DIR) -lft -lreadline

OBJ_DIR			= build
INCLUDE_DIRS	= includes $(LIBFT_DIR)/includes
INCLUDES		= $(foreach dir,$(INCLUDE_DIRS), -I$(dir))

GREEN			:= \033[0;32m
YELLOW			:= \033[0;33m
RED				:= \033[0;31m
BLUE			:= \033[0;34m
RESET			:= \033[0m

SRC				= \
					sources/lexer/lexer.c \
					sources/lexer/lexer_inputs.c \
					sources/lexer/lexer_utils.c \
					sources/main.c

OBJ				= $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC))

DEBUG ?= 0
ifeq ($(DEBUG), 1)
	CFLAGS += -g2 -O0 -fsanitize=leak
endif

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) $(LIB_FLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) --silent	

all: $(NAME) $(OBJ) $(LIBFT)

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) clean -C $(LIBFT_DIR) --silent

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) fclean -C $(LIBFT_DIR) --silent

re: fclean all

.PHONY: norminette make fclean clean re