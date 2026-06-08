/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osousa-d <osousa-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 21:47:33 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/06/07 22:13:07 by osousa-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "shell.h"
# include "enum.h"

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_env
{
	char			*value;
	char			*key;
	struct s_env	*next;
}	t_env;

typedef struct s_redir
{
	t_token_type	type;
	char			*file;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**args;
	char			**expanded_args;
	char			*path;
	t_builtin		builtin;
	t_redir			*redirs;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_pipe_data
{
	int	prev_pipe;
	int	fd[2];
}	t_pipe_data;

typedef struct s_shell
{
	t_env			*env;
	t_cmd			*cmd;
	t_token			*tokens;
	char			*input;
	char			*prompt_str;
	int				exit_code;
	int				exit_shell;
	int				std_out;
	int				std_in;
	t_pipe_data		pipe;
}	t_shell;



#endif