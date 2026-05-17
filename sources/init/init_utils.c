/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osousa-d <osousa-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 20:32:26 by osousa-d          #+#    #+#             */
/*   Updated: 2026/05/17 19:31:07 by osousa-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	env_add_back(t_env **head, t_env *current)
{
	t_env	*last;

	if (!*head)
		*head = current;
	else
	{
		last = *head;
		while (last->next)
			last = last->next;
		last->next = current;
	}
}

int	parser_env_line(char *str, t_env *node)
{
	char	*equal;

	equal = ft_strchr(str, '=');
	if (!equal)
	{
		if (!(node->key = ft_strdup(str)))
			return (0);
		node->value = NULL;
		return (1);
	}
	if (!(node->key = ft_substr(str, 0, equal - str)))
		return (0);
	if (!(node->value = ft_strdup(equal + 1)))
	{
		free_ptr((void **)&node->key);
		return (0);
	}
	return (1);
}

void	init_shell_values(t_shell *shell)
{
	shell->env = NULL;
	shell->cmd = NULL;
	shell->tokens = NULL;
	shell->input = NULL;
	shell->prompt_str = NULL;
	shell->exit_code = 0;
	shell->std_in = -1;
	shell->std_out = -1;
}

void	init_env_values(t_env *env)
{
	env->key = NULL;
	env->next = NULL;
	env->value = NULL;
}
