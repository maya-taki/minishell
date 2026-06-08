/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 18:43:36 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/06/07 23:10:37 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libftprintf/project/libft/libft.h"
# include "../libftprintf/project/src/ft_printf.h"
# include "structs.h"
# include "enum.h"

/*---------------------------------------------------------------------------*/
/*  DEFINES                                                                  */
/*---------------------------------------------------------------------------*/

# define MAX_PIPELINE	4096

# define Y		"\033[0;33m"
# define G		"\033[0;32m"
# define C		"\033[0;36m"
# define RED	"\033[0;31m"
# define RST	"\033[0m"

/*---------------------------------------------------------------------------*/
/*  INIT                                                                     */
/*---------------------------------------------------------------------------*/

int				init_shell(t_shell *shell, char **envp);
t_cmd			*init_cmd(void);

/*---------------------------------------------------------------------------*/
/*  LEXER                                                                    */
/*---------------------------------------------------------------------------*/

t_token			*lexer(char *input);
t_token			*read_token(char *input, int *i);
t_token			*handle_operator(t_token_type type, char *input, int *i);
t_token			*init_token(t_token_type type, char *value);
t_token_type	id_token_type(char *c, int *i);
char			*handle_word(char *input, int *i);
void			add_token(t_token **head, t_token *init_token);
void			update_quote_state(char c, t_quote_state *state);
void			free_tokens(t_token *tokens);
int				is_operator_valid(char *c);
int				is_operator(char c);
int				is_space(char c);
int				were_quotes_closed(char *input);

/*---------------------------------------------------------------------------*/
/*  PARSER                                                                   */
/*---------------------------------------------------------------------------*/

t_cmd			*parser(t_shell *shell);
t_cmd			*parser_handler(t_token *seg_start);
int				validate_syntax(t_token *tokens);
int				count_cmds(t_token *token_list);
int				count_words(t_token *token);
int				is_redir(t_token *token);
int				add_args(t_token *seg_start, t_cmd *cmd);
int				fill_args(t_token *seg_start, t_cmd *cmd);
int				add_redirs(t_token_type type, char *file, t_cmd *cmd);
int				fill_redirs(t_token *seg_start, t_cmd *cmd);
void			set_builtin(t_cmd *cmd);
// void			debug_print_cmds(t_cmd *cmds);
void			*free_single_cmd(t_cmd *cmd);
void			*free_all_cmds(t_cmd *cmds);
void			free_redir(t_redir *redirect);

/*---------------------------------------------------------------------------*/
/*  EXPANDER                                                                 */
/*---------------------------------------------------------------------------*/

void			expand_all(t_cmd *cmds, t_shell *shell);
char			*expand_word(const char *src, t_shell *shell);
char			*get_env_value(t_env *env, const char *name);
char			*append_char(char *dest, char c);
char			*append_str(char *dest, const char *src);
int				apply_redir(t_token *token, t_cmd **init_cmd, t_shell *shell);
int				expand_args(t_cmd *cmd, t_shell *shell);
int				expand_redirs(t_cmd *cmd, t_shell *shell);
int				replace_arg(char **arg_ptr, t_shell *shell);
int				is_single_quoted(char *arg);
void			update_quote_state_i(const char *src, t_quote_state *state,
					size_t *i);

/*---------------------------------------------------------------------------*/
/*  HEREDOC / REDIRECTS                                                      */
/*---------------------------------------------------------------------------*/

int				handle_heredoc(char *delimiter, t_shell *shell);
int				open_file(int *fd_ptr, char *path, int flags);
char			*remove_quotes(char *delimiter);
void			write_line(char *line, int fd);

/*---------------------------------------------------------------------------*/
/*  EXEC                                                                     */
/*---------------------------------------------------------------------------*/

int				execute(t_shell *shell);
int				exec_builtin(t_shell *shell, t_cmd *cmd);
int				exec_pipeline(t_shell *shell, t_cmd *cmd);
int				exec_external(t_shell *shell, t_cmd *cmd);
void			exec_child(t_shell *shell, t_cmd *cmd, char *exec_path);
void			exec_child_external(t_shell *shell, t_cmd *cmd);
void			setup_child_io(t_shell *shell);
void			reset_io(t_shell *shell);
char			*find_executable(char *cmd, t_shell *shell);
char			**build_envp(t_shell *shell);

/*---------------------------------------------------------------------------*/
/*  BUILTINS                                                                 */
/*---------------------------------------------------------------------------*/

int				builtin_echo(t_cmd *cmd);
int				builtin_cd(t_shell *shell);
int				builtin_pwd(t_shell *shell);
int				builtin_export(t_shell *shell);
int				builtin_unset(t_shell *shell);
int				builtin_env(t_shell *shell);
int				builtin_exit(t_shell *shell);

/*---------------------------------------------------------------------------*/
/*  SIGNALS                                                                  */
/*---------------------------------------------------------------------------*/

extern sig_atomic_t g_signal;

void	handle_sigint(int sig);
void	setup_signals(void);
void	setup_exec_signal(void);
void	setup_child_signal(void);
int		heredoc_event_hook(void);
int		prompt_event_hook(void);
void	handle_sigint_heredoc(int sig);
void	setup_heredoc_signals(void);
void 	proper_exit(t_shell *shell);

/*---------------------------------------------------------------------------*/
/*  ENV UTILS                                                                */
/*---------------------------------------------------------------------------*/

t_env			*env_new(char *key, char *value);
t_env			*create_env_node(char *env_line);
t_env			*find_env_node(t_env *env, char *key);
void			env_add_back(t_env **head, t_env *current);
char			*get_env_var(t_env *env, char *key);
int				set_env_var(t_env **env, char *key, char *value);
int				parser_env_line(char *str, char **key, char **value);
void			update_pwd_env(t_shell *shell, char *old_pwd);
int				count_env_vars(t_env *env);

/*---------------------------------------------------------------------------*/
/*  EXPORT UTILS                                                             */
/*---------------------------------------------------------------------------*/

void			sort_env_array(t_env **array, int count);
void			swap_env_nodes(t_env **a, t_env **b);
void			print_export_entry(t_env *node);
void			print_escaped_value(char *value);

/*---------------------------------------------------------------------------*/
/*  FORK / PATH UTILS                                                        */
/*---------------------------------------------------------------------------*/

char			*join_env_line(char *key, char *value);
char			*make_try_path(char *path, char *cmd);
int				get_exit_status(int status);

/*---------------------------------------------------------------------------*/
/*  EXIT UTILS                                                               */
/*---------------------------------------------------------------------------*/

int				get_sign_and_advance(const char **str);
long			get_max_digit(int sign);
int				check_overflow_and_add(long *result,
					long digit, long max_digit);
void			print_exit_error(const char *arg);
int				handle_no_arg_exit(t_shell *shell);
int				handle_invalid_arg_exit(t_shell *shell);

/*---------------------------------------------------------------------------*/
/*  ERROR UTILS                                                              */
/*---------------------------------------------------------------------------*/

const char		*error_msg(t_error_type error);
void			handle_error(t_error_type error, char *cmd, 
					char *context, int quotes);

/*---------------------------------------------------------------------------*/
/*  CLEAN / FREE                                                             */
/*---------------------------------------------------------------------------*/

void			free_ptr(void **ptr);
void			free_env_list(t_env *env);
void			free_shell(t_shell *shell);
void			free_paths(char **paths);
void			free_child(char *exec_path, char **envp, char **empty_envp);

#endif