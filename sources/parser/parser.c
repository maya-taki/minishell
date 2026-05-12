/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 19:00:55 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/05/11 20:15:27 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

int			fill_args(t_token *seg_start, t_cmd *cmd);
static int	add_args(t_token *seg_start, t_cmd *cmd);
int			fill_redirs(t_token *seg_start, t_cmd *cmd);
static int	add_redirs(t_token_type type, char *file, t_cmd *cmd);

int	fill_args(t_token *seg_start, t_cmd *cmd)
{
	cmd->cmd_args = malloc(sizeof(char *) * (count_words(seg_start) + 1));
	if (!cmd->cmd_args)
		return (0);
	if (!add_args(seg_start, cmd))
		return (0);
	return (1);
}

int	fill_redirs(t_token *seg_start, t_cmd *cmd)
{
	t_token	*tmp;

	tmp = seg_start;
	while (tmp && tmp->type != TOKEN_PIPE)
	{
		if (is_redir(tmp))
		{
			if (!tmp->next || tmp->type != TOKEN_WORD)
				return (ERR_SYNTAX);
			if (!add_redirs(tmp->type, tmp->value, cmd))
				return (ERR_MALLOC);
			tmp = tmp->next->next;
			continue ;
		}
		tmp = tmp->next;
	}
	return (1);
}

static int	add_args(t_token *seg_start, t_cmd *cmd)
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

static int	add_redirs(t_token_type type, char *file, t_cmd *cmd)
{
	t_redir	*redirect;
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
t_cmd	*parse_cmd(t_token *seg_start)
{
	t_cmd	*cmd;
	int		success;
	
	success = 0;
	cmd = new_cmd();
	success = fill_args(seg_start, cmd);
	if (!success)
		return (NULL);
	success = fill_redirs(seg_start, cmd);
	if (!success)
		return (NULL);
	return (cmd);
}

t_cmd	*parser(t_mini *mini)
{
	t_cmd	*head;
	t_cmd	*cmd;
	t_cmd	*last;
	t_token	*tmp;

	if (!mini || !mini->tokens)
		return (0);
	if (!validate_syntax(mini->tokens))
	{
		ft_printf(RED"Unknown token\n"RST);
		return (0);
	}
	tmp = mini->tokens;
	head = NULL;
	last = NULL;
	while (tmp)
	{
		cmd = parse_cmd(tmp);
		if (!cmd)
		{
			free_all_cmds(cmd);
			return (0);
		}
		if (!head)
			head = cmd;
		else
			last->next = cmd;
		last = cmd;
		while (tmp && tmp->type != TOKEN_PIPE)
			tmp = tmp->next;
		if (tmp && tmp->type == TOKEN_PIPE)
			tmp = tmp->next;
	}
	return (head);
}
