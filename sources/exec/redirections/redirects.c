/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 16:31:40 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/06/10 02:41:01 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

static int	open_file(int *fd_ptr, char *path, int flags)
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

static int	handle_redir(t_shell *shell, t_redir *redir)
{
	if (redir->type == TOKEN_REDIR_OUT)
	{
		if (open_file(&shell->std_out, redir->file,
				O_WRONLY | O_CREAT | O_TRUNC))
			return (1);
	}
	else if (redir->type == TOKEN_REDIR_APPEND)
	{
		if (open_file(&shell->std_out, redir->file,
				O_WRONLY | O_CREAT | O_APPEND))
			return (1);
	}
	else if (redir->type == TOKEN_REDIR_IN)
	{
		if (open_file(&shell->std_in, redir->file,
				O_RDONLY))
			return (1);
	}
	else if (redir->type == TOKEN_HEREDOC)
	{
		if (handle_heredoc(redir->file, shell) != 0)
			return (1);
	}
	return (0);
}

int	apply_redir(t_token *token, t_cmd *init_cmd, t_shell *shell)
{
	t_redir	*redir;
	t_cmd	*cmd;

	(void)token;
	if (!init_cmd)
		return (0);
	cmd = init_cmd;
	if (!cmd->redirs)
		return (0);
	redir = cmd->redirs;
	while (redir)
	{
		if (handle_redir(shell, redir) != 0)
			return (1);
		redir = redir->next;
	}
	return (0);
}
