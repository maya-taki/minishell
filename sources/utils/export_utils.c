/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copilot <copilot@example.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 23:00:00 by copilot          #+#    #+#             */
/*   Updated: 2026/06/04 23:00:00 by copilot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

int	count_env_vars(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

void	swap_env_nodes(t_env **a, t_env **b)
{
	t_env *tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	sort_env_array(t_env **array, int count)
{
	int i;
	int j;
	int min;

	i = 0;
	while (i < count)
	{
		min = i;
		j = i + 1;
		while (j < count)
		{
			if (ft_strcmp(array[j]->key, array[min]->key) < 0)
				min = j;
			j++;
		}
		if (min != i)
			swap_env_nodes(&array[i], &array[min]);
		i++;
	}
}

void	print_escaped_value(char *value)
{
	while (*value)
	{
		if (*value == '"' || *value == '\\' || *value == '$' || *value == '`')
			ft_printf("\\%c", *value);
		else
			ft_printf("%c", *value);
		value++;
	}
}

void	print_export_entry(t_env *node)
{
	if (!node->key)
		return ;
	if (!node->value)
	{
		ft_printf("declare -x %s\n", node->key);
		return ;
	}
	ft_printf("declare -x %s=\"", node->key);
	print_escaped_value(node->value);
	ft_printf("\"\n");
}
