/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osousa-d <osousa-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 00:00:00 by osousa-d          #+#    #+#             */
/*   Updated: 2026/06/05 06:08:58 by osousa-d         ###   ########.fr       */
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

static char	*find_executable(char *cmd, t_shell *shell)
{
	char	**paths;
	char	*path_env;
	char	*res;
	int		i;

	if (!cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	path_env = get_env_var(shell->env, "PATH");
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	i = 0;
	res = NULL;
	while (paths[i] && !res)
	{
		res = try_path(paths[i], cmd);
		i++;
	}
	free_paths(paths);
	return (res);
}

static void	free_envp_partial(char **envp, int i)
{
	while (i > 0)
	{
		i--;
		free(envp[i]);
	}
	free(envp);
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
	char	*exec_path;

	exec_path = find_executable(cmd->args[0], shell);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		if (exec_path)
			free(exec_path);
		return (1);
	}
	if (pid == 0)
		exec_child(shell, cmd, exec_path);
	if (exec_path)
		free(exec_path);
	if (waitpid(pid, &status, 0) == -1)
	{
		perror("waitpid");
		return (1);
	}
	tmp = get_exit_status(status);
	return (tmp);
}
