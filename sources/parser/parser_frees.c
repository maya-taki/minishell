/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_frees.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 14:52:39 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/05/26 18:21:03 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

void	free_redir(t_redir *redirect)
{
	t_redir	*tmp;

	tmp = redirect;
	while (tmp)
	{
		tmp = redirect->next;
		free(redirect->file);
		free(redirect);
		redirect = tmp;
	}
}

void	free_cmd_args(char **args)
{
	int	i;

	if (!args)
		return ;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

void	*free_cmds(t_cmd *cmd_list)
{
	t_cmd	*tmp;

	while (cmd_list)
	{
		tmp = cmd_list ->next;
		if (cmd_list->fd_in > 2)
			close(cmd_list->fd_in);
		if (cmd_list->fd_out > 2)
			close(cmd_list->fd_out);
		free_cmd_args(cmd_list->args);
		if (cmd_list->path)
			free(cmd_list->path);
		free(cmd_list);
		cmd_list = tmp;
	}
}
