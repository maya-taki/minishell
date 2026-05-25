/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otton-sousa <otton-sousa@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 00:19:40 by otton-sousa       #+#    #+#             */
/*   Updated: 2026/05/25 00:22:39 by otton-sousa      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

char	*get_env_var(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

t_env	*find_env_node(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env);
		env = env->next;		
	}
	return (NULL);
}

void	set_env_var(t_env **env, char *key, char *value)
{
	t_env	*node;
	t_env	*new_node;

	node = find_env_node(*env, key);
	if (node)
	{
		free(node->value);
		node->value = ft_strdup(value);
	}
	else
	{
		new_node = env_new(key, value);
		if (!new_node)
			return ;
		env_add_back(env, new_node);
	}
}

void	update_pwd_env(t_shell *shell, char *old_pwd)
{
	char	*new_pwd;

	if (!old_pwd)
		return ;
	new_pwd = getcwd(NULL, 0);
	set_env_var(&shell->env, "OLDPWD", old_pwd);
	if (new_pwd)
	{
		set_env_var(&shell->env, "PWD", new_pwd);
		free(new_pwd);
	}
	free(old_pwd);
}

