/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osousa-d <osousa-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 18:30:00 by osousa-d          #+#    #+#             */
/*   Updated: 2026/06/08 00:09:51 by osousa-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

static int	is_valid_identifier(char *str);
static int	parse_export_arg(char *arg, char **key, char **value);
static int	apply_export_arg(char *arg, t_shell *shell);
static int	print_export_env(t_shell *shell);

int	builtin_export(t_shell *shell)
{
	int	status;
	int	i;

	if (!shell || !shell->cmd || !shell->cmd->args)
		return (1);
	if (!shell->cmd->args[1])
		return (print_export_env(shell));
	status = 0;
	i = 1;
	while (shell->cmd->args[i])
	{
		if (apply_export_arg(shell->cmd->args[i], shell) != 0)
			status = 1;
		i++;
	}
	return (status);
}

static int	parse_export_arg(char *arg, char **key, char **value)
{
	char	*equal;

	equal = ft_strchr(arg, '=');
	if (!equal)
	{
		*key = ft_strdup(arg);
		if (!*key)
		{
			handle_error(ERR_MALLOC, "export", NULL, 0);
			return (1);
		}
		*value = NULL;
		return (0);
	}
	*key = ft_substr(arg, 0, equal - arg);
	if (!*key)
	{
		handle_error(ERR_MALLOC, "export", NULL, 0);
		return (1);
	}
	*value = ft_strdup(equal + 1);
	if (!*value)
	{
		free(*key);
		handle_error(ERR_MALLOC, "export", NULL, 0);
		return (1);
	}
	return (0);
}

static int	apply_export_arg(char *arg, t_shell *shell)
{
	char	*key;
	char	*value;
	int		status;

	key = NULL;
	value = NULL;
	if (!is_valid_identifier(arg))
	{
		handle_error(ERR_NOT_VALID_ID, "export", arg, 0);
		return (1);
	}
	else if (parse_export_arg(arg, &key, &value) != 0)
		return (1);
	else if (set_env_var(&shell->env, key, value) != 0)
	{
		status = 1;
		handle_error(ERR_MALLOC, "export", NULL, 0);
	}
	else
		status = 0;
	free(key);
	free(value);
	return (status);
}

void	fill_and_print_env(t_env *node, t_env **env_array,
								int count)
{
	int i;

	i = 0;
	while (node)
	{
		env_array[i] = node;
		node = node->next;
		i++;
	}
	sort_env_array(env_array, count);
	i = 0;
	while (i < count)
	{
		print_export_entry(env_array[i]);
		i++;
	}
}

static int	print_export_env(t_shell *shell)
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

static int	is_valid_identifier(char *str)
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
