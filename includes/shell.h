/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otton-sousa <otton-sousa@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 18:43:36 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/05/14 02:31:17 by otton-sousa      ###   ########.fr       */
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
# include "../libs/libft/libft.h"
# include "../libs/ft_printf/ft_printf.h"
# include "structs.h"
# include "error_handler.h"

/*###LEXER###*/
t_token	*new_token(t_token_type type, char *value);
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

// Init_utils
void	env_add_back(t_env **head, t_env *current);
void	parser_env_line(char *str, t_env *node);

// Init
t_cmd	*init_cmd(char *input);
t_shell	*init_shell(t_shell *shell, char **envp); // principal


// Builtins
int			builtin_echo(t_cmd *cmd);
int			builtin_pwd(void);
int			builtin_cd(t_cmd *cmd, t_env **env);
t_builtin	get_builtin(char *arg);



// Exec
t_cmd	*create_test_cmd(void); // remove
void	exec_builtin(t_shell *shell);
void	execute(t_shell *shell);




#endif
