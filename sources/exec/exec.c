/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 11:33:05 by osousa-d          #+#    #+#             */
/*   Updated: 2026/05/14 22:21:50 by mtakiyos         ###   ########.fr       */
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

t_cmd *create_test_cmd(void)
{
	t_cmd		*cmd;
	static char	*arr[] = {"echo", "hello", "world", NULL};

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd_args = arr;
	cmd->builtin = ECHO;
	cmd->redirs = NULL;
	cmd->next = NULL;
	return (cmd);
}

void	exec_builtin(t_mini *mini)
{
	// decide qual func_builtin chamar
	if (mini->cmd->builtin == ECHO)
		builtin_echo(mini->cmd);
	if (mini->cmd->builtin == PWD)
		builtin_pwd();
	if (mini->cmd->builtin == CD)
		builtin_cd(mini->cmd, mini->env_list);
}

void	execute(t_mini *mini)
{
	if (mini->cmd->builtin != NONE)
		exec_builtin(mini);
	// else
	// 	exec_external(cmd);
}
