/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 18:43:36 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/05/14 17:02:22 by mtakiyos         ###   ########.fr       */
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

# define Y		"\033[0;33m"
# define G		"\033[0;32m"
# define C		"\033[0;36m"
# define RED	"\033[0;31m"
# define RST	"\033[0m"

/*#LEXER#*/
t_token			*lexer(char *input);
int				is_operator_valid(char *c);
int				is_space(char c);
int				is_operator(char c);
char			*handle_word(char *input, int *i);
t_token			*handle_operator(t_token_type type, char *input, int *i);
void			update_quote_state(char c, t_quote_state *state);
int				were_quotes_closed(char *input);
t_token			*new_token(t_token_type type, char *value);
t_token_type	id_token_type(char *c, int *i);
t_token			*read_token(char *input, int *i);
void			add_token(t_token **head, t_token *new);
void			free_tokens(t_token *tokens);

/*#PARSER#*/
int				validate_syntax(t_token *tokens);
int				count_cmds(t_token *token_list);
int				count_words(t_token *token);
int				is_redir(t_token *token);
t_cmd			*new_cmd(void);
int				open_file(int *fd_ptr, char *path, int flags);
void			free_single_cmd(t_cmd *cmd);
void			free_all_cmds(t_cmd *cmds);
void			free_redir(t_redir *redirect);
t_cmd			*parser(t_mini *mini);

/*###EXPANDER###*/
int				open_file(int *fd_ptr, char *path, int flags);

/*###UTILS###*/
const char		*error_msg(t_error_type error);
int				handle_error(t_error_type error, char *cmd, char *context);

#endif
