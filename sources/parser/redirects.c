/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 14:32:53 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/05/08 17:12:57 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

// static int	handle_heredoc(t_token *tmp, t_cmd **flags);
// static int	handle_output(t_token *tmp, t_cmd **flags);
// static int	handle_append(t_token *tmp, t_cmd **flags);
// static int	handle_input(t_token *tmp, t_cmd **flags);

// static int	handle_redir(t_token *token)
// {
// 	if (token->type == TOKEN_HEREDOC)
// 		return (handle_heredoc());
// 	if (token->type == TOKEN_REDIR_OUT)
// 		return (handle_output());
// 	if (token->type == TOKEN_REDIR_APPEND)
// 		return (handle_apprend());
// 	if (token->type == TOKEN_REDIR_IN)
// 		return (handle_input());
// }

int	is_redir(t_token *token)
{
	return (token->type == TOKEN_HEREDOC
			|| token->type == TOKEN_REDIR_OUT
			|| token->type == TOKEN_REDIR_APPEND
			|| token->type == TOKEN_REDIR_IN);
}