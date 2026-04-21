NAME			= minishell
CC				= cc
CFLAGS			= -Werror -Wextra -Wall -g

# ================= LIBS =================

LIBFT_DIR		= libs/libft
PRINTF_DIR		= libs/ft_printf

LIBFT			= $(LIBFT_DIR)/libft.a
PRINTF			= $(PRINTF_DIR)/ft_printf.a

LIB_FLAGS = $(PRINTF) \
            -L$(LIBFT_DIR) -lft \
            -lreadline

# ================= INCLUDES =================

OBJ_DIR			= build
INCLUDE_DIRS	= includes $(LIBFT_DIR)/includes $(PRINTF_DIR)/includes
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
					sources/builtin/builtin_echo.c \
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

.PHONY: all clean fclean re