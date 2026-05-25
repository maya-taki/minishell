/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otton-sousa <otton-sousa@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 19:35:32 by osousa-d          #+#    #+#             */
/*   Updated: 2026/05/24 21:54:23 by otton-sousa      ###   ########.fr       */
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
// arrumar em pastas
t_env	*env_new(char *key, char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = ft_strdup(key);
	if (!node->key)
	{
		free(node);
		return (NULL);
	}
	if (value)
	{
		node->value = ft_strdup(value);
		if (!node->value)
		{
			free(node->key);
			free(node);
			return (NULL);
		}
	}
	else
		node->value = NULL;
	node->next = NULL;
	return (node);
}

t_env	*create_env_node(char *env_line)
{
	t_env	*node;
	char	*key;
	char	*value;

	if (!parser_env_line(env_line, &key, &value))
		return (NULL);
	node = env_new(key, value);
	free(key);
	free(value);
	if (!node)
		return (NULL);
	return (node);
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
		current = create_env_node(envp[i]);
		if (!current)
		{
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


