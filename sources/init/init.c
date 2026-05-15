/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otton-sousa <otton-sousa@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 19:35:32 by osousa-d          #+#    #+#             */
/*   Updated: 2026/05/14 02:54:55 by otton-sousa      ###   ########.fr       */
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

t_cmd	*init_cmd(char *input)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = ft_split(input, ' ');
	if (!cmd->args || !cmd->args[0])
	{
		free_cmd(cmd);
		return (NULL);
	}
	cmd->builtin = get_builtin(cmd->args[0]);
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
			return (NULL);
		current->next = NULL;
		parser_env_line(envp[i], current);
		env_add_back(&head, current);
		i++;
	}
	return (head);
}

t_shell	*init_shell(t_shell *shell, char **envp)
{
	shell->cmd = NULL;
	shell->env = init_env(envp);
	shell->exit_status = 0;
}


