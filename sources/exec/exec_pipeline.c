/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 13:12:07 by osousa-d          #+#    #+#             */
/*   Updated: 2026/06/08 21:35:19 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

static void	reset_shell_io(t_shell *shell)
{
	shell->std_in = STDIN_FILENO;
	shell->std_out = STDOUT_FILENO;
}

static void	setup_pipe_io(t_shell *shell, t_cmd *cmd)
{
	reset_shell_io(shell);
	apply_redir(NULL, &cmd, shell);
	if (shell->pipe.prev_pipe != -1
		&& shell->std_in == STDIN_FILENO)
		shell->std_in = shell->pipe.prev_pipe;
	if (shell->pipe.fd[1] != -1
		&& shell->std_out == STDOUT_FILENO)
		shell->std_out = shell->pipe.fd[1];
	setup_child_io(shell);
}

static void	run_pipeline_child(t_shell *shell, t_cmd *cmd)
{
	pid_t	pid;

	setup_pipe_io(shell, cmd);
	if (shell->pipe.prev_pipe != -1)
		close(shell->pipe.prev_pipe);
	if (shell->pipe.fd[1] != -1)
		close(shell->pipe.fd[1]);
	if (cmd->builtin != NONE)
	{
		free_env_list(shell->env);
		free_tokens(shell->tokens);
		pid = exec_builtin(shell, cmd);
		free_all_cmds(cmd);
		exit(pid);
	}
	exec_child_external(shell, cmd);
}

static pid_t	fork_cmd(t_shell *shell, t_cmd *cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return ((pid_t)-1);
	}
	if (pid == 0)
	{
	if (shell->pipe.fd[0] != -1
		&& shell->pipe.fd[0] != shell->pipe.prev_pipe)
		close(shell->pipe.fd[0]);
	run_pipeline_child(shell, cmd);
	}
	if (shell->pipe.fd[1] != -1)
	close(shell->pipe.fd[1]);
	return (pid);
}

static int	wait_all(pid_t *pids, int n)
{
	int	i;
	int	status;
	int	last;

	i = 0;
	last = 0;
	setup_exec_signal();
	while (i < n)
	{
		waitpid(pids[i], &status, 0);
		if (i == n - 1)
			last = get_exit_status(status);
		i++;
	}
	setup_signals();
	return (last);
}

static int	handle_pipeline_cmd(t_shell *shell,
	t_cmd *cmd, pid_t *pid)
{
	shell->pipe.fd[0] = -1;
	shell->pipe.fd[1] = -1;

	if (cmd->next)
	{
		if (pipe(shell->pipe.fd) == -1)
			return (perror("pipe"), 1);
	}
	*pid = fork_cmd(shell, cmd);
	if (*pid == -1)
		return (1);

	if (shell->pipe.prev_pipe != -1)
		close(shell->pipe.prev_pipe);

	if (cmd->next)
		shell->pipe.prev_pipe = shell->pipe.fd[0];
	else
		shell->pipe.prev_pipe = -1;
	return (0);
}

int	exec_pipeline(t_shell *shell, t_cmd *cmd)
{
	pid_t	pids[MAX_PIPELINE];
	int		n;

	shell->pipe.prev_pipe = -1;
	shell->pipe.fd[0] = -1;
	shell->pipe.fd[1] = -1;
	n = 0;
	while (cmd && n < MAX_PIPELINE)
	{
		if (handle_pipeline_cmd(shell, cmd, &pids[n]))
			return (1);
		cmd = cmd->next;
		n++;
	}
	if (shell->pipe.prev_pipe != -1)
		close(shell->pipe.prev_pipe);
	return (wait_all(pids, n));
}
