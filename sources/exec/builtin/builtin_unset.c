/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osousa-d <osousa-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 18:33:00 by osousa-d          #+#    #+#             */
/*   Updated: 2026/06/07 23:56:12 by osousa-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

static int	is_valid_identifier(char *str);
static void	unset_env_var(t_env **env, char *key);

int	builtin_unset(t_shell *shell)
{
	int	i;
	int	status;

	if (!shell || !shell->cmd || !shell->cmd->args)
		return (1);
	status = 0;
	i = 1;
	while (shell->cmd->args[i])
	{
		if (!is_valid_identifier(shell->cmd->args[i]))
		{
			status = 1;
			handle_error(ERR_NOT_VALID_ID, "unset", shell->cmd->args[i], 0);
		}
		else
			unset_env_var(&shell->env, shell->cmd->args[i]);
		i++;
	}
	return (status);
}

static int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	unset_env_var(t_env **env, char *key)
{
	t_env	*prev;
	t_env	*curr;

	prev = NULL;
	curr = *env;
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			if (prev)
				prev->next = curr->next;
			else
				*env = curr->next;
			free(curr->key);
			free(curr->value);
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}
