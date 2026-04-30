/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 18:43:36 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/04/29 19:48:21 by mtakiyos         ###   ########.fr       */
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
t_token			*lexer(char *input, int i);
int				invalid_operator(char *c, int i);
int				is_space(char c);
int				is_invalid(char c);
int				is_operator(char c);
char			*handle_word(char *input, int *i);


t_token_type	id_token_type(char *str, int *i);
t_token			*next_token(char *input, int *i);

void			update_quote_state(char c, t_quote_state *state);
int				validade_quotes(char *input);


void			free_tokens(t_token *tokens);
t_token			*new_token(t_token_type type, char *value);
void			add_token(t_token **head, t_token *new);

//void			validate_argc(int ac, char **av);
//int			verify_syntax(t_mini *mini);

#endif