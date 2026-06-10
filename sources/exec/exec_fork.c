/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osousa-d <osousa-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 00:00:00 by osousa-d          #+#    #+#             */
/*   Updated: 2026/06/09 20:45:47 by osousa-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

static char	*try_path(char *dir, char *cmd)
{
	char	*full;

	full = make_try_path(dir, cmd);
	if (!full)
		return (NULL);
	if (access(full, X_OK) == 0)
		return (full);
	free(full);
	return (NULL);
}

char	*find_executable(char *cmd, t_shell *shell)
{
	char	**paths;
	char	*path_env;
	char	*path;
	char	*res;
	int		i;

	if (!cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		path = ft_strdup(cmd);
		return (path);
	}
	path_env = get_env_var(shell->env, "PATH");
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	i = 0;
	res = NULL;
	while (paths[i] && !res)
		res = try_path(paths[i++], cmd);
	free_arr(paths);
	return (res);
}

char	**build_envp(t_shell *shell)
{
	char	**envp;
	t_env	*cur;
	int		i;
	int		count;

	count = count_env_vars(shell->env);
	envp = malloc(sizeof(char *) * (count + 1));
	if (!envp)
		return (NULL);
	cur = shell->env;
	i = 0;
	while (cur)
	{
		envp[i] = join_env_line(cur->key, cur->value);
		if (!envp[i])
		{
			free_envp_partial(envp, i);
			return (NULL);
		}
		i++;
		cur = cur->next;
	}
	envp[i] = NULL;
	return (envp);
}

int	exec_external(t_shell *shell, t_cmd *cmd)
{
	pid_t	pid;
	int		status;
	int		tmp;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}
	if (pid == 0)
	{
		setup_child_io(shell);
		exec_child_external(shell, cmd);
	}
	reset_io(shell);
	if (waitpid(pid, &tmp, 0) == -1)
	{
		perror("waitpid");
		return (1);
	}
	status = get_exit_status(tmp);
	return (status);
}
