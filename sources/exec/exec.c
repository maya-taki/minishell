/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otton-sousa <otton-sousa@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 11:33:05 by osousa-d          #+#    #+#             */
/*   Updated: 2026/05/25 01:07:45 by otton-sousa      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

void	exec_builtin(t_shell *shell)
{
	// decide qual func_builtin chamar
	if (shell->cmd->builtin == ECHO)
		builtin_echo(shell->cmd);
	else if (shell->cmd->builtin == PWD)
		builtin_pwd();
	else if (shell->cmd->builtin == CD)
		builtin_cd(shell);
}

void	execute(t_shell *shell)
{
	if (shell->cmd->builtin != NONE)
		exec_builtin(shell);
	// else
	// 	exec_external(cmd);
}
