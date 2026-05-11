/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 19:00:55 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/05/11 04:56:59 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

int		fill_args(t_token *seg_start, t_cmd *cmd)
{
	int 	i;
	t_token *tmp;

	cmd->cmd_args = malloc(sizeof(char *) * (count_words(seg_start) + 1));
	if (!cmd->cmd_args)
		return (0);
	i = 0;
	tmp = seg_start;
	while (tmp && tmp->type != TOKEN_PIPE)
	{
		if (is_redir(tmp))
		{
			tmp = tmp->next;
			if (tmp)
				tmp = tmp->type;
			continue ;
		}
		if (tmp->type == TOKEN_WORD)
		{
			cmd->cmd_args[i] = ft_strdup(tmp->value);
			if (!cmd->cmd_args[i])
				return (0);
			i++;
		}
		tmp = tmp->next;
	}
	cmd->cmd_args[i] = NULL;
	return (1);
}
int		fill_redirs(t_token *seg_start, t_cmd *cmd)
{
	t_token	*tmp;

	tmp = seg_start;
	while (tmp && tmp->type != TOKEN_PIPE)
	{
		if (is_redir(tmp))
		{
			if (!tmp->next || tmp->type != TOKEN_WORD)
				return (ERR_SYNTAX);
			if (!add_redir(tmp->type, tmp->value, cmd))
				return (ERR_MALLOC);
			tmp = tmp->next->next;
			continue ;
		}
		tmp = tmp->next;
	}
	return (1);
}

int		add_redir(t_token_type type, char *file, t_cmd *cmd)
{
	t_redir *redirect;
	t_redir	*last;
	
	redirect = malloc(sizeof(t_redir));
	if (!redirect)
		return (0);
	redirect->type = type;
	redirect->file = ft_strdup(file);
	if (!redirect->file)
	{
		free(redirect);
		return (0);
	}
	redirect->next = NULL;
	if (!cmd->redirs)
	{
		cmd->redirs = redirect;
		return (1);
	}
	last = cmd->redirs;
	while (last->next)
		last = last->next;
	last->next = redirect;
	return (1);
}

t_cmd	*new_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd_args = NULL;
	cmd->cmd_path = NULL;
	cmd->redirs = NULL;
	cmd->next = NULL;
	return (cmd);
}

void	free_redir(t_redir *redirect)
{
	t_redir *tmp;

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
	
	while(cmds)
	{
		tmp = cmds->next;
		free_single_cmd(cmds);
		cmds = tmp;
	}
}


