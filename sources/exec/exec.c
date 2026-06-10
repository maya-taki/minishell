/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 11:33:05 by osousa-d          #+#    #+#             */
/*   Updated: 2026/06/09 22:31:14 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

int	exec_builtin(t_shell *shell, t_cmd *cmd)
{
	int	status;

	status = 1;
	if (cmd->builtin == ECHO)
		status = builtin_echo(cmd);
	else if (cmd->builtin == PWD)
		status = builtin_pwd(shell);
	else if (cmd->builtin == CD)
		status = builtin_cd(shell);
	else if (cmd->builtin == EXPORT)
		status = builtin_export(shell);
	else if (cmd->builtin == UNSET)
		status = builtin_unset(shell);
	else if (cmd->builtin == ENV)
		status = builtin_env(shell);
	else if (cmd->builtin == EXIT)
		status = builtin_exit(shell);
	return (status);
}

static int	run_builtin_with_redir(t_shell *shell, t_cmd *cmd)
{
	int	saved_in;
	int	saved_out;
	int	status;

	saved_in = dup(STDIN_FILENO);
	saved_out = dup(STDOUT_FILENO);
	if (apply_redir(NULL, cmd, shell) != 0)
	{
		reset_io(shell);
		return (1);
	}
	setup_child_io(shell);
	status = exec_builtin(shell, cmd);
	dup2(saved_in, STDIN_FILENO);
	dup2(saved_out, STDOUT_FILENO);
	close(saved_in);
	close(saved_out);
	reset_io(shell);
	return (status);
}

static int	run_single(t_shell *shell, t_cmd *cmd)
{
	int	status;

	status = 0;
	if (apply_redir(NULL, cmd, shell) != 0)
	{
		reset_io(shell);
		return (shell->exit_code);
	}
	if (!cmd->args || !cmd->args[0] || cmd->args[0][0] == '\0')
	{
		reset_io(shell);
		return (shell->exit_code);
	}
	if (cmd->builtin != NONE)
		return (run_builtin_with_redir(shell, cmd));
	status = exec_external(shell, cmd);
	return (status);
}

int	execute(t_shell *shell)
{
	int		status;
	t_cmd	*head;

	if (!shell)
		return (1);
	if (!shell->cmd)
		return (shell->exit_code);
	head = shell->cmd;
	if (!shell->cmd->next)
		status = run_single(shell, shell->cmd);
	else
		status = exec_pipeline(shell, shell->cmd);
	shell->cmd = head;
	shell->exit_code = status;
	return (status);
}
