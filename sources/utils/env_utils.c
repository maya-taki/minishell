/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osousa-d <osousa-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 23:35:36 by otton-sousa       #+#    #+#             */
/*   Updated: 2026/06/05 03:45:27 by osousa-d         ###   ########.fr       */
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

int	parser_env_line(char *str, char **key, char **value)
{
	char	*equal;

	equal = ft_strchr(str, '=');
	if (!equal)
	{
		*key = ft_strdup(str);
		*value = NULL;
		if (!*key)
			return (0);
		return (1);
	}
	*key = ft_substr(str, 0, equal - str);
	if (!*key)
		return (0);
	*value = ft_strdup(equal + 1);
	if (!*value)
	{
		free(*key);
		return (0);
	}
	return (1);
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
