/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osousa-d <osousa-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 19:37:06 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/06/04 17:38:57 by osousa-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

int	fill_args(t_token *seg_start, t_cmd *cmd);
int	fill_redirs(t_token *seg_start, t_cmd *cmd);
int	add_args(t_token *seg_start, t_cmd *cmd);
int	add_redirs(t_token_type type, char *file, t_cmd *cmd);

static void	set_builtin(t_cmd *cmd)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return ;
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		cmd->builtin = ECHO;
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		cmd->builtin = CD;
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		cmd->builtin = PWD;
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		cmd->builtin = EXPORT;
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		cmd->builtin = UNSET;
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		cmd->builtin = ENV;
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		cmd->builtin = EXIT;
	else
		cmd->builtin = NONE;
}

t_cmd	*parser_handler(t_token *seg_start)
{
	t_cmd	*cmd;

	cmd = init_cmd();
	if (!cmd)
		return (NULL);
	if (fill_args(seg_start, cmd) != 0)
		return (free_single_cmd(cmd));
	set_builtin(cmd);
	if (fill_redirs(seg_start, cmd) != 0)
		return (free_single_cmd(cmd));
	return (cmd);
}

int	fill_args(t_token *seg_start, t_cmd *cmd)
{
	cmd->args = malloc(sizeof(char *) * (count_words(seg_start) + 1));
	if (!cmd->args)
		return (1);
	return (add_args(seg_start, cmd));
}

int	fill_redirs(t_token *seg_start, t_cmd *cmd)
{
	t_token	*tmp;

	tmp = seg_start;
	while (tmp && tmp->type != TOKEN_PIPE)
	{
		if (is_redir(tmp))
		{
			if (!tmp->next || tmp->next->type != TOKEN_WORD)
				return (ERR_SYNTAX);
			if (add_redirs(tmp->type, tmp->next->value, cmd) != 0)
				return (ERR_MALLOC);
			tmp = tmp->next->next;
			continue ;
		}
		tmp = tmp->next;
	}
	return (0);
}

int	add_args(t_token *seg_start, t_cmd *cmd)
{
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = seg_start;
	while (tmp && tmp->type != TOKEN_PIPE)
	{
		if (is_redir(tmp))
		{
			tmp = tmp->next;
			if (tmp)
				tmp = tmp->next;
			continue ;
		}
		if (tmp->type == TOKEN_WORD)
		{
			cmd->args[i] = ft_strdup(tmp->value);
			if (!cmd->args[i])
				return (1);
			i++;
		}
		tmp = tmp->next;
	}
	cmd->args[i] = NULL;
	return (0);
}

int	add_redirs(t_token_type type, char *file, t_cmd *cmd)
{
	t_redir	*redirect;
	t_redir	*last;

	redirect = malloc(sizeof(t_redir));
	if (!redirect)
		return (1);
	redirect->type = type;
	redirect->file = ft_strdup(file);
	if (!redirect->file)
	{
		free(redirect);
		return (1);
	}
	redirect->next = NULL;
	if (!cmd->redirs)
	{
		cmd->redirs = redirect;
		return (0);
	}
	last = cmd->redirs;
	while (last->next)
		last = last->next;
	last->next = redirect;
	return (0);
}
