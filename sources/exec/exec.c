/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osousa-d <osousa-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 11:33:05 by osousa-d          #+#    #+#             */
/*   Updated: 2026/06/04 20:20:11 by osousa-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

int	exec_builtin(t_shell *shell)
{
	int	status;

	status = 1;
	if (!shell || !shell->cmd)
		return (status);
	if (shell->cmd->builtin == ECHO)
		status = builtin_echo(shell->cmd);
	else if (shell->cmd->builtin == PWD)
		status = builtin_pwd(shell);
	else if (shell->cmd->builtin == CD)
		status = builtin_cd(shell);
	else if (shell->cmd->builtin == EXPORT)
		status = builtin_export(shell);
	else if (shell->cmd->builtin == UNSET)
		status = builtin_unset(shell);
	else if (shell->cmd->builtin == ENV)
		status = builtin_env(shell);
	else if (shell->cmd->builtin == EXIT)
		status = builtin_exit(shell);
	return (status);
}

int	execute(t_shell *shell)
{
	t_cmd	*head;
	t_cmd	*cmd;
	int		status;

	if (!shell)
		return (1);
	status = shell->exit_code;
	if (!shell->cmd)
		return (status);
	head = shell->cmd;
	cmd = shell->cmd;
	while (cmd)
	{
		shell->cmd = cmd;
		if (cmd->builtin != NONE)
		{
			status = exec_builtin(shell);
			shell->exit_code = status;
		}
		if (shell->exit_shell)
			break ;
		cmd = cmd->next;
	}
	shell->cmd = head;
	return (status);
}
