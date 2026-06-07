/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osousa-d <osousa-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 18:35:00 by osousa-d          #+#    #+#             */
/*   Updated: 2026/06/06 22:41:07 by osousa-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

int	builtin_env(t_shell *shell)
{
	t_env	*node;

	if (!shell || !shell->cmd || !shell->env)
		return (1);
	if (shell->cmd->args[1])
	{
		handle_error(ERR_NO_FILE, "env", shell->cmd->args[1], 0);
		return (127);
	}
	node = shell->env;
	while (node)
	{
		if (node->key && node->value)
			ft_printf("%s=%s\n", node->key, node->value);
		node = node->next;
	}
	return (0);
}
