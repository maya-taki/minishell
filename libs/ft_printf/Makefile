# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: otton-sousa <otton-sousa@student.42.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/11 20:54:01 by osousa-d          #+#    #+#              #
#    Updated: 2026/02/08 20:36:34 by otton-sousa      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_printf.a

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC =	ft_print_char.c \
		ft_print_str.c \
		ft_print_hex.c \
		ft_print_nbr.c \
		ft_print_pointer.c \
		ft_print_unsigned.c \
		ft_printf.c

OBJ_DIR = obj
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

LIBFT_DIR = ../libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@ar rcs $(NAME) $(OBJ)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@make --no-print-directory -C $(LIBFT_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@make --no-print-directory clean -C $(LIBFT_DIR)

fclean: clean
	@rm -f $(NAME)
	@make --no-print-directory fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
