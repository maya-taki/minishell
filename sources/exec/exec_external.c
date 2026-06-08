/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 05:52:31 by osousa-d          #+#    #+#             */
/*   Updated: 2026/06/07 22:14:12 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

void	setup_child_io(t_shell *shell)
{
	setup_child_signal();
	if (shell->std_in != STDIN_FILENO)
	{
		dup2(shell->std_in, STDIN_FILENO);
		close(shell->std_in);
	}
	if (shell->std_out != STDOUT_FILENO)
	{
		dup2(shell->std_out, STDOUT_FILENO);
		close(shell->std_out);
	}
}

static void	try_exec(char *path, t_cmd *cmd, char **envp)
{
	if (path)
		execve(path, cmd->args, envp);
	else
		execve(cmd->args[0], cmd->args, envp);
}

static void	cmd_not_found(char *name)
{
	ft_putstr_fd(name, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
}
 
void	exec_child_external(t_shell *shell, t_cmd *cmd)
{
	char		**envp;
	char		*exec_path;
	static char	*empty_envp[] = {NULL};
 
	exec_path = find_executable(cmd->args[0], shell);
	if (!exec_path)
	{
		cmd_not_found(cmd->args[0]);
		free_all_cmds(shell->cmd);
		free_tokens(shell->tokens);
		free_env_list(shell->env);
		exit(127);
	}
	envp = build_envp(shell);
	if (!envp)
		envp = empty_envp;
	try_exec(exec_path, cmd, envp);
	perror(cmd->args[0]);
	free_child(exec_path, envp, empty_envp);
	exit(126);
}