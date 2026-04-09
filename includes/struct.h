/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 21:47:33 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/04/08 22:10:11 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "shell.h"

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_HEREDOC,
	// TOKEN_SINGLE_QUOTE,
	// TOKEN_DOUBLE_QUOTE,
	// TOKEN_VAR,
	// TOKEN_AND,
	// TOKEN_OR,
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
}	t_token;
