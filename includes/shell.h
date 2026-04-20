/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 18:43:36 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/04/20 18:56:21 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libftprintf/project/libft/libft.h"
# include "../libftprintf/project/src/ft_printf.h"
# include "structs.h"
# include "error_handler.h"

#define Y		"\033[0;33m"
#define G		"\033[0;32m"
#define C		"\033[0;36m"
#define RED		"\033[0;31m"
#define RST		"\033[0m"

/*###LEXER###*/
t_token	*new_token(t_token_type type, char *value);
t_token	*lexer(char *input);
void	add_token(t_token **head, t_token *new);
int		invalid_operator(char *c, int i);
int		is_space(char c);
int		is_invalid(char c);
int		is_quote(char c);
int		is_operator(char c);
void	handle_operator(t_token *tokens, char *input, int *i);
void	handle_word(t_token **head, char *input, int *i);

// void	read_input_redir_in(t_token **head, char *input, int *i);
// void	read_input_redir_out(t_token **head, char *input, int *i);

void	print_tokens(t_token *head);
void	validate_argc(int ac, char **av);

#endif
