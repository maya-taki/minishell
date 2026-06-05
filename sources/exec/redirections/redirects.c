/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 16:31:40 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/06/04 21:28:17 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

static int	handle_append(t_token *tmp, t_shell *shell) // >>
{
	if (open_file(&shell->std_out, tmp->next->value,
			O_WRONLY | O_CREAT | O_APPEND))
		return (0);
	return (1);
}

static int	handle_output(t_token *tmp, t_shell *shell) // >
{
	if (open_file(&shell->std_out, tmp->next->value,
			O_WRONLY | O_CREAT | O_TRUNC))
		return (0);
	return (1);
}

static int	handle_input(t_token *tmp, t_shell *shell) // <
{
	if (open_file(&shell->std_in, tmp->next->value,
			O_RDONLY))
		return (0);
	return (1);
}

int	handle_redirection(t_token *token, t_cmd **init_cmd, t_shell *shell)
{
	(void)init_cmd;
	if (token->type == TOKEN_REDIR_OUT)
		return (handle_output(token, shell));
	else if (token->type == TOKEN_REDIR_APPEND)
		return (handle_append(token, shell));
	else if (token->type == TOKEN_REDIR_IN)
		return (handle_input(token, shell));
	else if (token->type == TOKEN_HEREDOC)
		return (handle_heredoc(token->next->value, shell));
	return (1);
}
