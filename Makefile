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
					sources/main.c \
					sources/init/init.c \
					sources/lexer/lexer.c \
					sources/lexer/lexer_inputs.c \
					sources/lexer/lexer_utils.c \
					sources/lexer/lexer_free.c \
					sources/lexer/tokens.c \
					sources/parser/parser.c \
					sources/parser/parser_handler.c \
					sources/parser/syntax.c \
					sources/parser/parser_utils.c \
					sources/parser/parser_frees.c \
					sources/expander/expander_utils.c \
					sources/expander/expander.c \
					sources/exec/redirections/redirects.c \
					sources/exec/redirections/heredoc.c \
					sources/exec/redirections/redir_utils.c \
					sources/exec/exec.c \
					sources/exec/builtin/builtin_cd.c \
					sources/exec/builtin/builtin_echo.c \
					sources/exec/builtin/builtin_pwd.c \
					sources/utils/error_utils.c \
					sources/utils/env_utils.c \
					sources/utils/cd_utils.c \
					sources/clean/clear.c \
					sources/clean/free_init.c

OBJ				= $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC))

# ================= DEBUG =================

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

TEST_EXPANDER = tests/test_expander.c
TEST_EXPANDER_NAME = test_expander
TEST_REDIRECTS = tests/test_redirects.c
TEST_REDIRECTS_NAME = test_redirects

test-expander: $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) $(TEST_EXPANDER) sources/expander/expander.c sources/expander/expander_utils.c sources/lexer/lexer_utils.c sources/utils/env_utils.c sources/clean/free_init.c $(LIB_FLAGS) -o $(TEST_EXPANDER_NAME)

test-redirects: $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) $(TEST_REDIRECTS) sources/exec/redirections/redirects.c $(LIB_FLAGS) -o $(TEST_REDIRECTS_NAME)

.PHONY: norminette make fclean clean re test-expander test-redirects