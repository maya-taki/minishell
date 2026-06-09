/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 05:38:55 by osousa-d          #+#    #+#             */
/*   Updated: 2026/06/08 21:41:38 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

char	*join_env_line(char *key, char *value)
{
	char	*tmp;
	char	*env_line;

	tmp = ft_strjoin(key, "=");
	if (!tmp)
		return (NULL);
	if (value)
		env_line = ft_strjoin(tmp, value);
	else
		env_line = ft_strdup(tmp);
	free(tmp);
	return (env_line);
}

char	*make_try_path(char *path, char *cmd)
{
	char	*tmp;
	char	*try;

	tmp = ft_strjoin(path, "/");
	if (!tmp)
		return (NULL);
	try = ft_strjoin(tmp, cmd);
	free(tmp);
	return (try);
}

int	get_exit_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (status);
}
