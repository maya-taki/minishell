/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otton-sousa <otton-sousa@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 16:39:06 by osousa-d          #+#    #+#             */
/*   Updated: 2026/05/25 00:38:40 by otton-sousa      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	free_ptr(void **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

void	free_env_node(t_env *node)
{
	free(node->key);
	free(node->value);
	free(node);
}

void	free_env_list(t_env *env)
{
	t_env	*next;

	while (env)
	{
		next = env->next;
		free_env_node(env);
		env = next;
	}
}

void	close_fd(int *fd)
{	
	if (*fd >= 0)
	{
		close(*fd);
		*fd = -1;
	}
}

void	free_shell(t_shell *shell)
{
	if (!shell)
		return ;
	if (shell->env)
	{
		free_env_list(shell->env);
		shell->env = NULL;
	}
	if (shell->tokens)
	{
		free_tokens(shell->tokens);
		shell->tokens = NULL;
	}
	if (shell->cmd)
	{
		free_all_cmds(shell->cmd);
		shell->cmd = NULL;
	}
	free_ptr((void **)&shell->input);
	free_ptr((void **)&shell->prompt_str);
	if (shell->std_in >= 0)
		close_fd(&shell->std_in);
	if (shell->std_out >= 0)
		close_fd(&shell->std_out);
}
