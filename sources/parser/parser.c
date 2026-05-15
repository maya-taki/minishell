/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osousa-d <osousa-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 19:00:55 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/05/15 11:04:15 by osousa-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

int			fill_args(t_token *seg_start, t_cmd *cmd);
static int	add_args(t_token *seg_start, t_cmd *cmd);
int			fill_redirs(t_token *seg_start, t_cmd *cmd);
static int	add_redirs(t_token_type type, char *file, t_cmd *cmd);

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

static int	add_redirs(t_token_type type, char *file, t_cmd *cmd)
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
t_cmd	*parse_cmd(t_token *seg_start)
{
	t_cmd	*cmd;

	cmd = new_cmd();
	if (!cmd)
		return (NULL);
	if (fill_args(seg_start, cmd) != 0)
	{
		free_single_cmd(cmd);
		return (NULL);
	}
	if (fill_redirs(seg_start, cmd) != 0)
	{
		free_single_cmd(cmd);	
		return (NULL);
	}
	return (cmd);
}

static int	validate_parser(t_shell *shell)
{
	if (!shell || !shell->tokens)
		return (1);
	if (validate_syntax(shell->tokens) != 0)
	{
		handle_error(ERR_SYNTAX, NULL, "`newline'");
		return (1);
	}
	return (0);
}

t_cmd	*parser(t_shell *shell)
{
	t_cmd	*head;
	t_cmd	*cmd;
	t_cmd	*last;
	t_token	*tmp;

	if (validate_parser(shell) != 0)
		return (NULL);
	tmp = shell->tokens;
	head = NULL;
	last = NULL;
	while (tmp)
	{
		cmd = parse_cmd(tmp);
		if (!cmd)
		{
			free_all_cmds(head);
			return (NULL);
		}
		if (!head)
			head = cmd;
		else
			last->next = cmd;
		last = cmd;
		while (tmp && tmp->type != TOKEN_PIPE)
			tmp = tmp->next;
		if (tmp)
			tmp = tmp->next;
	}
	return (head);
}
