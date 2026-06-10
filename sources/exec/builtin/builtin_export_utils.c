/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 22:50:50 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/06/09 22:51:35 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	print_export_env(t_shell *shell)
{
	t_env	**env_array;
	t_env	*node;
	int		count;

	if (!shell)
		return (1);
	count = count_env_vars(shell->env);
	env_array = malloc(sizeof(t_env *) * count);
	if (!env_array)
	{
		handle_error(ERR_MALLOC, "export", NULL, 0);
		return (1);
	}
	node = shell->env;
	fill_and_print_env(node, env_array, count);
	free(env_array);
	return (0);
}
