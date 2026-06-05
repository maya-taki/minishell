/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osousa-d <osousa-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 11:33:05 by osousa-d          #+#    #+#             */
/*   Updated: 2026/06/05 13:33:39 by osousa-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

int	exec_builtin(t_shell *shell, t_cmd *cmd)
{
	if (cmd->builtin == ECHO)
		return (builtin_echo(cmd));
	if (cmd->builtin == PWD)
		return (builtin_pwd(shell));
	if (cmd->builtin == CD)
		return (builtin_cd(shell));
	if (cmd->builtin == EXPORT)
		return (builtin_export(shell));
	if (cmd->builtin == UNSET)
		return (builtin_unset(shell));
	if (cmd->builtin == ENV)
		return (builtin_env(shell));
	if (cmd->builtin == EXIT)
		return (builtin_exit(shell));
	return (1);
}
 
static int	count_cmds_exec(t_cmd *cmd)
{
	int	n;
 
	n = 0;
	while (cmd)
	{
		n++;
		cmd = cmd->next;
	}
	return (n);
}

static int	run_single(t_shell *shell, t_cmd *cmd)
{
	int	status;

	apply_redir(NULL, &cmd, shell);
	if (cmd->builtin != NONE)
		status = exec_builtin(shell, cmd);
	else
		status = exec_external(shell, cmd);
	reset_io(shell);
	return (status);
}
 
int	execute(t_shell *shell)
{
	int		status;
	t_cmd	*head;

	if (!shell || !shell->cmd)
		return (1);
	head = shell->cmd;
	if (count_cmds_exec(shell->cmd) == 1)
		status = run_single(shell, shell->cmd);
	else
		status = exec_pipeline(shell, shell->cmd);
	shell->cmd = head;
	shell->exit_code = status;
	return (status);
}
