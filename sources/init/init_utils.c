/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otton-sousa <otton-sousa@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 20:32:26 by osousa-d          #+#    #+#             */
/*   Updated: 2026/05/14 02:55:19 by otton-sousa      ###   ########.fr       */
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

void	parser_env_line(char *str, t_env *node)
{
	char	*equal;

	equal = ft_strchr(str, '=');
	if (!equal)
	{
		node->key = ft_strdup(str);
		node->value = NULL;
		return ;
	}
	node->key = ft_substr(str, 0, equal - str);
	node->value = ft_strdup(equal + 1);
	return ;
}
