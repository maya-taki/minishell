/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 23:00:00 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/06/09 23:01:18 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

void	reset_shell_io(t_shell *shell)
{
	if (shell->std_in != STDIN_FILENO && shell->std_in != -1)
		close(shell->std_in);
	if (shell->std_out != STDOUT_FILENO && shell->std_out != -1)
		close(shell->std_out);
	shell->std_in = STDIN_FILENO;
	shell->std_out = STDOUT_FILENO;
}

int	wait_all(pid_t *pids, int n)
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
