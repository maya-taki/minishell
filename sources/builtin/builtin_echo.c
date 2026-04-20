/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osousa-d <osousa-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 12:01:34 by osousa-d          #+#    #+#             */
/*   Updated: 2026/04/19 21:22:54 by osousa-d         ###   ########.fr       */
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

int	verify_flag_n(char **argv)
{
	int	i;
	
	
	while ()
	{
		/* code */
	}
	

}
void	builtin_echo(t_cmd *cmd)
{
	int	newline;

	if (cmd->argv[1] == )
}

t_cmd	*exec_bultin(t_cmd *cmd)
{
	// decide qual func_builtin chamar
	if (cmd->builtin == ECHO)
		builtin_echo(cmd);
}
