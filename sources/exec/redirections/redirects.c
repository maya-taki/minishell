/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 16:31:40 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/06/04 23:55:29 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

int	open_file(int *fd_ptr, char *path, int flags)
{
	if (*fd_ptr > 2)
		close(*fd_ptr);
	*fd_ptr = open(path, flags, 0644);
	if (*fd_ptr == -1)
	{
		perror(path);
		return (1);
	}
	return (0);
}

static int handle_redirections(t_shell *shell, t_redir *redir)
{
	if (redir->type == TOKEN_REDIR_OUT)
	{
		if (open_file(&shell->std_out, redir->file, O_WRONLY | O_CREAT | O_TRUNC))
			return (1);
	}
	else if (redir->type == TOKEN_REDIR_APPEND)
	{
		if (open_file(&shell->std_out, redir->file, O_WRONLY | O_CREAT | O_APPEND))
			return (1);
	}
	else if (redir->type == TOKEN_REDIR_IN)
	{
		if (open_file(&shell->std_in, redir->file, O_RDONLY))
			return (1);
	}
	else if (redir->type == TOKEN_HEREDOC)
	{
		if (handle_heredoc(redir->file, shell) != 0)
			return (1);
	}
	return (0);
}

int	redirections(t_token *token, t_cmd **init_cmd, t_shell *shell)
{
	t_redir	*redir;
	t_cmd	*cmd;

	(void)token;
	if (!init_cmd || !*init_cmd)
		return (0);
	
	cmd = *init_cmd;
	if (!cmd->redirs)
		return (0);
	
	redir = cmd->redirs;
	while (redir)
	{
		handle_redirections(shell, redir);
		if (!handle_redirections)
			return (0);
		redir = redir->next;
	}
	return (0);
}
