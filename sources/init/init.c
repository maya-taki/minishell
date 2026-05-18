/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otton-sousa <otton-sousa@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 19:35:32 by osousa-d          #+#    #+#             */
/*   Updated: 2026/05/18 00:15:50 by otton-sousa      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

t_cmd	*init_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->cmd_path = NULL;
	cmd->redirs = NULL;
	cmd->next = NULL;
	return (cmd);
}

static t_env	*init_env(char **envp)
{
	t_env	*current;
	t_env	*head;
	int		i;

	i = 0;
	head = NULL;
	while (envp[i])
	{
		current = malloc(sizeof(t_env));
		if (!current)
		{
			free_env_list(head);
			return (NULL);
		}
		init_env_values(current);
		if (!parser_env_line(envp[i], current))
		{
			free_env_node(current);
			free_env_list(head);
			return (NULL);
		}
		env_add_back(&head, current);
		i++;
	}
	return (head);
}

int	init_shell(t_shell *shell, char **envp)
{
	init_shell_values(shell);
	if (!(shell->env = init_env(envp)))
	{
		free_shell(shell);
		return (0);
	}
	if ((shell->std_in = dup(STDIN_FILENO)) == -1)
	{
		free_shell(shell);
		return (0);
	}
	if ((shell->std_out = dup(STDOUT_FILENO)) == -1)
	{
		free_shell(shell);
		return (0);
	}
	return (1);
}


