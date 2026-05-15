/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osousa-d <osousa-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 19:35:32 by osousa-d          #+#    #+#             */
/*   Updated: 2026/05/15 11:40:53 by osousa-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

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

int	init_shell(t_shell *shell, char **envp)
{
	if (!(shell->env = init_env(envp)))
		return (0); // sem clean
	shell->cmd = NULL;
	shell->tokens = NULL;
	shell->input = NULL;
	shell->prompt_str = NULL;
	shell->exit_code = 0;
	shell->std_in = dup(STDIN_FILENO); // precisa tratar a restauração dos fd (dup2)
	if (shell->std_in == -1)
		return (0); // fazer função que da free na env;
	shell->std_out = dup(STDOUT_FILENO); // precisa tratar a restauração dos fd (dup2)
	if (shell->std_out == -1)
		return (0); // chamar função que limpa a env e fecha stdin
	return (1);
}


