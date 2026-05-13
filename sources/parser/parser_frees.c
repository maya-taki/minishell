/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_frees.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 14:52:39 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/05/13 18:59:05 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

void	free_single_cmd(t_cmd *cmd);
void	free_all_cmds(t_cmd *cmds);
void	free_redir(t_redir *redirect);

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

void	free_single_cmd(t_cmd *cmd)
{
	int	i;

	if (!cmd)
		return ;
	if (cmd->cmd_args)
	{
		i = 0;
		while (cmd->cmd_args[i])
			free(cmd->cmd_args[i++]);
		free(cmd->cmd_args);
	}
	free(cmd->cmd_path);
	free_redir(cmd->redirs);
	free(cmd);
}

void	free_all_cmds(t_cmd *cmds)
{
	t_cmd	*tmp;

	while (cmds)
	{
		tmp = cmds->next;
		free_single_cmd(cmds);
		cmds = tmp;
	}
}
