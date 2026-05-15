NAME			= minishell
CC				= cc
CFLAGS			= -Werror -Wextra -Wall -g

LIBFT_DIR		= libftprintf/project
LIBFT			= $(LIBFT_DIR)/libftprintf.a
LIB_FLAGS		= -L$(LIBFT_DIR) -lftprintf -lreadline

OBJ_DIR			= build
INCLUDE_DIRS	= includes $(LIBFT_DIR) $(LIBFT_DIR)/libft
INCLUDES		= $(foreach dir,$(INCLUDE_DIRS), -I$(dir))

# ================= COLORS =================

GREEN			:= \033[0;32m
YELLOW			:= \033[0;33m
RED				:= \033[0;31m
BLUE			:= \033[0;34m
RESET			:= \033[0m

# ================= SOURCES =================

SRC				= \
					sources/lexer/lexer.c \
					sources/lexer/lexer_inputs.c \
					sources/lexer/lexer_utils.c \
					sources/lexer/tokens.c \
					sources/utils/error_utils.c \
					sources/parser/parser_utils.c \
					sources/parser/parser.c \
					sources/parser/parser_frees.c \
					sources/parser/syntax.c \
					sources/builtin/builtin_echo.c \
					sources/builtin/builtin_pwd.c \
					sources/exec/exec.c \
					sources/main.c

OBJ				= $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC))

# ================= DEBUG =================

DEBUG ?= 0
ifeq ($(DEBUG), 1)
	CFLAGS += -g2 -O0 -fsanitize=leak
endif

# ================= BUILD =================

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) $(OBJ) $(PRINTF) $(LIBFT) -lreadline -o $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# ================= LIBS BUILD =================

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) --silent

$(PRINTF):
	@$(MAKE) -C $(PRINTF_DIR) --silent

# ================= CLEAN =================

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) clean -C $(LIBFT_DIR) --silent
	@$(MAKE) clean -C $(PRINTF_DIR) --silent

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) fclean -C $(LIBFT_DIR) --silent
	@$(MAKE) fclean -C $(PRINTF_DIR) --silent

re: fclean all

.PHONY: norminette make fclean clean re
