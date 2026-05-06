/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 21:47:33 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/05/05 22:28:17 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

#include "shell.h"

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_HEREDOC,
}	t_token_type;

typedef enum e_quote_state
{
	QUOTE_NONE,
	QUOTE_DOUBLE,
	QUOTE_SINGLE,
}	t_quote_state;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
} t_token;

typedef struct s_env
{
	char			*value;
	char			*key;
	struct s_env	*next;
} t_env;

typedef struct s_redir
{
	t_token_type	*type;
	char			*file;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**cmd_args;
	char			*cmd_path;
	t_redir	 		*redirs;
	struct s_cmd	*next;
} t_cmd;

typedef struct s_mini
{
	t_env			*env_list;
	t_cmd			*cmd;
	t_token			*tokens;
	char			*input;
	char			*prompt_str;
	int				exit_code;
	int				std_out;
	int				std_in;
	struct s_mini	*next;
} t_mini;


#endif
