/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 22:29:37 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/05/06 14:37:21 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

static int	handle_heredoc(t_token *tmp, t_cmd **flags)
{
	
}

static int	handle_output(t_token *tmp, t_cmd **flags)
{
	if(open)
}
static int	handle_append(t_token *tmp, t_cmd **flags);

static int	handle_input(t_token *tmp, t_cmd **flags);

static int	is_redirect(t_token *token)
{
	if (token->type == TOKEN_HEREDOC)
		return (handle_heredoc());
	if (token->type == TOKEN_REDIR_OUT)
		return (handle_output());
	if (token->type == TOKEN_REDIR_APPEND)
		return (handle_apprend());
	if (token->type == TOKEN_REDIR_IN)
		return (handle_input());
}

static int	handle_redirections(t_token *token)
{
	if (token->type == TOKEN_HEREDOC)
		return (1);
	if (token->type == TOKEN_REDIR_OUT)
		return (1);
	if (token->type == TOKEN_REDIR_APPEND)
		return (1);
	if (token->type == TOKEN_REDIR_IN)
		return (1);
	return (0);
}

verify_syntax();