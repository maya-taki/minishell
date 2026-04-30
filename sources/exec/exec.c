/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osousa-d <osousa-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 11:33:05 by osousa-d          #+#    #+#             */
/*   Updated: 2026/04/29 20:56:57 by osousa-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

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

t_cmd *create_test_cmd(void)
{
	t_cmd		*cmd;
	static char	*arr[] = {"echo", "hello", "world", NULL};

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = arr;
	cmd->builtin = ECHO;
	cmd->redir = NULL;
	cmd->next = NULL;
	return (cmd);
}

void	exec_builtin(t_shell *shell)
{
	// decide qual func_builtin chamar
	if (shell->cmd->builtin == ECHO)
		builtin_echo(shell->cmd);
	if (shell->cmd->builtin == PWD)
		builtin_pwd();
	if (shell->cmd->builtin == CD)
		builtin_cd(shell->cmd, shell->env);
}

void	execute(t_shell *shell)
{
	if (shell->cmd->builtin != NONE)
		exec_builtin(shell);
	// else
	// 	exec_external(cmd);
}
