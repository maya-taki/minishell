/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 16:31:40 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/05/26 19:59:46 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

static int	handle_append(t_token *tmp, t_cmd **cmd)
{
	
	if (open_file(&(*cmd)->fd_out, tmp->next->value,
			 O_WRONLY | O_CREAT | O_APPEND))
		return(0);
	return (1);
}

static int	handle_output(t_token *tmp, t_cmd **cmd)
{
	
	if (open_file(&(*cmd)->fd_out, tmp->next->value,
			O_WRONLY | O_CREAT | O_TRUNC))
		return(0);
	return (1);
}

static int	handle_input(t_token *tmp, t_cmd **cmd)
{
	
	if (open_file(&(*cmd)->fd_in, tmp->next->value,
			O_RDONLY))
		return(0);
	return (1);
}

// static int	handle_heredoc(char *delimiter, t_cmd **cmd, t_shell *shell)
// {
	
// 	if (open_file( O_WRONLY, O_CREAT, O_APPEND))
// 


int	handle_redir(t_token *token, t_cmd **new_cmd, t_shell *shell)
{
	if (token->type == TOKEN_REDIR_OUT)
		return (handle_output(token, new_cmd));
	else if (token->type == TOKEN_REDIR_APPEND)
		return (handle_append(token, new_cmd));
	else if (token->type == TOKEN_REDIR_IN)
		return (handle_input(token, new_cmd));
	else if (token->type == TOKEN_HEREDOC)
		return (handle_heredoc(token->next->next, *new_cmd, shell));
	return (1);
}
