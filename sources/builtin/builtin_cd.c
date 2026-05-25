/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otton-sousa <otton-sousa@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 19:03:52 by osousa-d          #+#    #+#             */
/*   Updated: 2026/05/24 22:17:07 by otton-sousa      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

static char	*get_cd_path(t_shell *shell);

int	builtin_cd(t_shell *shell)
{
	char *old_pwd;
	char *path;
	
	if (shell->cmd->args[2])
	{
		handle_error(ERR_TOO_MANY_ARGS, "cd", NULL);
		return (0);
	}
	path = get_cd_path(shell);
	if (!path)
		return (0);
	old_pwd = getcwd(NULL, 0);
	if (chdir(path) == -1)
	{
		perror("minishell: cd");
		free(old_pwd);
		return (0);
	}
	update_pwd_env(shell, old_pwd);
	return (1);
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

static char	*get_cd_path(t_shell *shell)
{
	char *home;

	if (shell->cmd->args[1])
			return (shell->cmd->args[1]);
	home = get_env_var(shell->env, "HOME");
	if (!home)
	{
		handle_error(ERR_HOME_NOT_SET, "cd", NULL);
		return (NULL);
	}
	return (home);
}

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
