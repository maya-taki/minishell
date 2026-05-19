/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enum.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 10:57:53 by osousa-d          #+#    #+#             */
/*   Updated: 2026/05/19 20:18:29 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUM_H
# define ENUM_H

# include "shell.h"
# include "structs.h"

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

typedef enum e_builtin
{
	NONE,
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT
}	t_builtin;

typedef enum e_error_type
{
	ERR_NONE,
	ERR_PARSE,
	ERR_SYNTAX,
	ERR_CMD_NOT_FOUND,
	ERR_NO_FILE,
	ERR_PERMISSION,
	ERR_MALLOC,
	ERR_TOO_MANY_ARGS,
	ERR_NUM_REQUIRED,
	ERR_NOT_VALID_ID,
	ERR_HOME_NOT_SET,
	ERR_OLDPWD_NOT_SET
}	t_error_type;

#endif
