/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osousa-d <osousa-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 00:00:00 by osousa-d          #+#    #+#             */
/*   Updated: 2026/06/05 13:36:24 by osousa-d         ###   ########.fr       */
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
		res = try_path(paths[i++], cmd);
	free_paths(paths);
	return (res);
}
 
static void	free_envp_partial(char **envp, int i)
{
	while (i > 0)
	{
		--i;
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
			return (free_envp_partial(envp, i), NULL);
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
	char	*exec_path;
 
	exec_path = find_executable(cmd->args[0], shell);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), free(exec_path), 1);
	if (pid == 0)
		exec_child(shell, cmd, exec_path);
	free(exec_path);
	if (waitpid(pid, &status, 0) == -1)
		return (perror("waitpid"), 1);
	return (get_exit_status(status));
}
