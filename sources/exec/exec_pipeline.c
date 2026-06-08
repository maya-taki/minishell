/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 13:12:07 by osousa-d          #+#    #+#             */
/*   Updated: 2026/06/07 22:10:20 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

static void	reset_shell_io(t_shell *shell)
{
	shell->std_in = STDIN_FILENO;
	shell->std_out = STDOUT_FILENO;
}

static void	setup_pipe_io(t_shell *shell, t_cmd *cmd, int pipe_in, int pipe_out)
{
	reset_shell_io(shell);
	apply_redir(NULL, &cmd, shell);
	if (pipe_in != -1 && shell->std_in == STDIN_FILENO)
		shell->std_in = pipe_in;
	if (pipe_out != -1 && shell->std_out == STDOUT_FILENO)
		shell->std_out = pipe_out;
	setup_child_io(shell);
}

static void	run_pipeline_child(t_shell *shell, t_cmd *cmd, int pipe_in, int pipe_out)
{
	setup_pipe_io(shell, cmd, pipe_in, pipe_out);
	if (pipe_in != -1)
		close(pipe_in);
	if (pipe_out != -1)
		close(pipe_out);
	if (cmd->builtin != NONE)
		exit(exec_builtin(shell, cmd));
	exec_child_external(shell, cmd);
}

static pid_t	fork_cmd(t_shell *shell, t_cmd *cmd, int pipe_in, int pipe_out)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (perror("fork"), (pid_t)-1);
	if (pid == 0)
		run_pipeline_child(shell, cmd, pipe_in, pipe_out);
	if (pipe_in != -1)
		close(pipe_in);
	if (pipe_out != -1)
		close(pipe_out);
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

static int	handle_pipeline_cmd(t_shell *shell, t_cmd *cmd, int *pipe_in, pid_t *pid)
{
	int	fd[2];
	int	pipe_out;

	pipe_out = -1;
	if (cmd->next)
	{
		if (pipe(fd) == -1)
		{
			perror("pipe");
			return (1);
		}
		pipe_out = fd[1];
	}
	*pid = fork_cmd(shell, cmd, *pipe_in, pipe_out);
	if (*pid == -1)
		return (1);
	if (cmd->next)
		*pipe_in = fd[0];
	else
		*pipe_in = -1;
	return (0);
}

int	exec_pipeline(t_shell *shell, t_cmd *cmd)
{
	pid_t	pids[MAX_PIPELINE];
	int		pipe_in;
	int		n;

	pipe_in = -1;
	n = 0;
	while (cmd && n < MAX_PIPELINE)
	{
		if (handle_pipeline_cmd(shell, cmd, &pipe_in, &pids[n]))
			return (1);
		cmd = cmd->next;
		n++;
	}
	if (pipe_in != -1)
		close(pipe_in);
	return (wait_all(pids, n));
}
