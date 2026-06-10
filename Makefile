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
					sources/utils/lexer_utils.c \
					sources/clean/lexer_free.c \
					sources/lexer/tokens.c \
					sources/parser/parser.c \
					sources/parser/parser_handler.c \
					sources/parser/syntax.c \
					sources/utils/parser_utils.c \
					sources/clean/parser_frees.c \
					sources/utils/expander_utils.c \
					sources/expander/expander.c \
					sources/expander/append.c \
					sources/exec/redirections/redirects.c \
					sources/exec/redirections/heredoc.c \
					sources/exec/exec.c \
					sources/exec/exec_fork.c \
					sources/exec/exec_external.c \
					sources/exec/exec_pipeline.c \
					sources/exec/exec_pipeline_utils.c \
					sources/exec/builtin/builtin_cd.c \
					sources/exec/builtin/builtin_echo.c \
					sources/exec/builtin/builtin_pwd.c \
					sources/exec/builtin/builtin_export.c \
					sources/exec/builtin/builtin_export_utils.c \
					sources/exec/builtin/builtin_unset.c \
					sources/exec/builtin/builtin_env.c \
					sources/exec/builtin/builtin_exit.c \
					sources/signal/signal.c \
					sources/signal/signal_heredoc.c \
					sources/utils/error_utils.c \
					sources/utils/export_utils.c \
					sources/utils/exit_utils.c \
					sources/utils/env_utils.c \
					sources/utils/cd_utils.c \
					sources/utils/fork_utils.c \
					sources/utils/io_utils.c \
					sources/clean/free.c \
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

libft: $(LIBFT)
	
re: fclean all

val: readline.supp all
	@/bin/valgrind --suppressions=readline.supp \
				--leak-check=full \
				--show-leak-kinds=all \
				--track-origins=yes \
				--track-fds=yes \
				--trace-children=yes \
				--trace-children-skip='*/bin/*,*/sbin/*,/usr/bin/*' \
				./${NAME}


.PHONY: norminette make fclean clean re
