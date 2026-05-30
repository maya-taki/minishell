/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 18:43:36 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/05/29 18:43:12 by mtakiyos         ###   ########.fr       */
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
# include "enum.h"

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
t_token			*init_token(t_token_type type, char *value);
void			add_token(t_token **head, t_token *init_token);
t_token_type	id_token_type(char *c, int *i);
t_token			*read_token(char *input, int *i);
void			free_tokens(t_token *tokens);

/*#PARSER#*/
int				validate_syntax(t_token *tokens);
int				count_cmds(t_token *token_list);
int				count_words(t_token *token);
int				is_redir(t_token *token);
t_cmd			*init_cmd(void);
void			*free_single_cmd(t_cmd *cmd);
void			*free_all_cmds(t_cmd *cmds);
void			free_redir(t_redir *redirect);
t_cmd			*parser_handler(t_token *seg_start);
t_cmd			*parser(t_shell *shell);

int				add_args(t_token *seg_start, t_cmd *cmd);
int				fill_args(t_token *seg_start, t_cmd *cmd);
int				add_redirs(t_token_type type, char *file, t_cmd *cmd);
int				fill_redirs(t_token *seg_start, t_cmd *cmd);
void			debug_print_cmds(t_cmd *cmds);


/*###EXPANDER###*/
int				open_file(int *fd_ptr, char *path, int flags);
int				handle_redir(t_token *token, t_cmd **init_cmd, t_shell *shell);
void			remove_quotes(char *delimiter);



/*###CLEAN###*/
void			free_ptr(void **ptr);
void			free_env_node(t_env *node);
void			free_env_list(t_env *env);
void			close_fd(int *fd);
void			free_shell(t_shell *shell);

/*###UTILS###*/
const char		*error_msg(t_error_type error);
int				handle_error(t_error_type error, char *cmd, char *context);
void			env_add_back(t_env **head, t_env *current);
t_env			*env_new(char *key, char *value);
int				parser_env_line(char *str, char **key, char **value);
t_env			*create_env_node(char *env_line);
char			*get_env_var(t_env *env, char *key);
t_env			*find_env_node(t_env *env, char *key);
void			set_env_var(t_env **env, char *key, char *value);
void			update_pwd_env(t_shell *shell, char *old_pwd);

/*###INIT###*/
t_cmd			*init_cmd(void);
int				init_shell(t_shell *shell, char **envp);

/*###BUILTIN###*/
int				builtin_echo(t_cmd *cmd);
int				builtin_cd(t_shell *shell);
int				builtin_pwd(void);


/*###EXEC###*/
void			exec_builtin(t_shell *shell);
void			execute(t_shell *shell);

	// // Exec
	// t_cmd	*create_test_cmd(void); // remove
	// void	exec_builtin(t_shell *shell);
	// void	execute(t_shell *shell);

#endif
