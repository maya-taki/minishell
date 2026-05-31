/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osousa-d <osousa-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 19:03:52 by osousa-d          #+#    #+#             */
/*   Updated: 2026/05/31 17:35:26 by osousa-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

static char	*get_cd_path(t_shell *shell);

int	builtin_cd(t_shell *shell)
{
	char	*old_pwd;
	char	*path;

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
