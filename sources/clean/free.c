/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osousa-d <osousa-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 19:34:32 by osousa-d          #+#    #+#             */
/*   Updated: 2026/06/09 20:57:01 by osousa-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	free_arr(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_envp_partial(char **envp, int i)
{
	while (i > 0)
	{
		--i;
		free(envp[i]);
	}
	free(envp);
}

void	free_child(char *exec_path, char **envp, char **empty_envp)
{
	if (exec_path)
		free(exec_path);
	if (envp && envp != empty_envp)
		free_arr(envp);
}
