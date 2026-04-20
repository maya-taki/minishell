/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osousa-d <osousa-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 11:33:05 by osousa-d          #+#    #+#             */
/*   Updated: 2026/04/19 22:27:29 by osousa-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"


// typedef struct s_cmd
// {
// 	char			**argv;
// 	t_builtin		builtin;
// 	t_redir			*redir;
// 	struct s_cmd	*next;
// }	t_cmd;

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
	cmd->argv = arr;
	cmd->builtin = ECHO;
	cmd->redir = NULL;
	cmd->next = NULL;
	return (cmd);
}

t_cmd	*exec_bultin(t_cmd *cmd)
{
	// decide qual func_builtin chamar
	if (cmd->builtin == ECHO)
		builtin_echo(cmd);
}

void	execute(t_cmd *cmd)
{
	if (cmd->builtin != NONE)
		exec_builtin(cmd);
	else
		exec_external(cmd);
}
