/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otton-sousa <otton-sousa@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 11:33:05 by osousa-d          #+#    #+#             */
/*   Updated: 2026/05/18 00:23:08 by otton-sousa      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

// typedef enum e_builtin
// {
// 	NONE,
// 	ECHO,
// 	CD,
// 	PWD,
// 	EXPORT,
// 	UNSET,
// 	ENV,
// 	EXIT
// }	t_builtin;

void	exec_builtin(t_shell *shell)
{
	// decide qual func_builtin chamar
	if (shell->cmd->builtin == ECHO)
		builtin_echo(shell->cmd);
	else if (shell->cmd->builtin == PWD)
		builtin_pwd();
	else if (shell->cmd->builtin == CD)
		builtin_cd(shell->cmd, shell->env);
}

void	execute(t_shell *shell)
{
	if (shell->cmd->builtin != NONE)
		exec_builtin(shell);
	// else
	// 	exec_external(cmd);
}
