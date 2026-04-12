/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 18:43:36 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/04/11 20:34:31 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include "../printf/ft_printf.h"
# include "structs.h"
# include "error_handler.h"

/*###LEXER###*/
t_token *new_token(t_token_type type, char *value);
void	add_token(t_token **head, t_token *new);
void	handle_inputs(t_token *token, char *input, int *i);
t_token	*lexer(char *input);
int		is_operator(char c);
int		skip_spaces(char *input, int *i);

void	read_input_pipe(t_token **head, char *input, int *i);
void	read_input_and(t_token **head, char *input, int *i);
void	read_input_redir_in(t_token **head, char *input, int *i);
void	read_input_redir_out(t_token **head, char *input, int *i);
void	read_input_word(t_token **head, char *input);

#endif
