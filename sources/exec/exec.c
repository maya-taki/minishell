/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osousa-d <osousa-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 11:33:05 by osousa-d          #+#    #+#             */
/*   Updated: 2026/06/06 22:16:36 by osousa-d         ###   ########.fr       */
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

static int	run_builtin_with_redir(t_shell *shell, t_cmd *cmd)
{
	int	saved_in;
	int	saved_out;
	int	status;
 
	saved_in = dup(STDIN_FILENO);
	saved_out = dup(STDOUT_FILENO);
	if (apply_redir(NULL, &cmd, shell) != 0)
		return (reset_io(shell), 1);
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
	if (cmd->builtin != NONE)
		return (run_builtin_with_redir(shell, cmd));
	if (apply_redir(NULL, &cmd, shell) != 0)
		return (reset_io(shell), 1);
	return (exec_external(shell, cmd));
}
 
int	execute(t_shell *shell)
{
	int		status;
	t_cmd	*head;
 
	if (!shell || !shell->cmd)
		return (shell ? shell->exit_code : 1);
	head = shell->cmd;
	if (!shell->cmd->next)
		status = run_single(shell, shell->cmd);
	else
		status = exec_pipeline(shell, shell->cmd);
	shell->cmd = head;
	shell->exit_code = status;
	return (status);
}