/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osousa-d <osousa-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 05:52:31 by osousa-d          #+#    #+#             */
/*   Updated: 2026/06/05 06:23:31 by osousa-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

static void	try_exec(char *path, t_cmd *cmd, char **envp)
{
	if (path)
		execve(path, cmd->args, envp);
	else
		execve(cmd->args[0], cmd->args, envp);
}

static void	setup_child_io(t_shell *shell)
{
	if (shell->std_in != STDIN_FILENO)
		dup2(shell->std_in, STDIN_FILENO);
	if (shell->std_out != STDOUT_FILENO)
		dup2(shell->std_out, STDOUT_FILENO);
}

void	exec_child(t_shell *shell, t_cmd *cmd, char *exec_path)
{
	char		**envp;
	static char	*empty_envp[] = {NULL};

	setup_child_io(shell);
	envp = build_envp(shell);
	if (!envp)
		envp = empty_envp;
	try_exec(exec_path, cmd, envp);
	perror(cmd->args[0]);
	free_child(exec_path, envp, empty_envp);
	exit(127);
}
