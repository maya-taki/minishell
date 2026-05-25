/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otton-sousa <otton-sousa@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 19:00:55 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/05/25 00:48:03 by otton-sousa      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

t_cmd	*parse_cmd(t_token *seg_start)
{
	t_cmd	*cmd;

	cmd = init_cmd();
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

static t_cmd	*run_parse(t_cmd *head, t_cmd *cmd, t_cmd *last, t_token *tmp)
{
	while (tmp)
	{
		cmd = parse_cmd(tmp);
		if (!cmd)
			return (free_all_cmds(head), NULL);
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
	cmd = NULL;
	run_parse(head, cmd, last, tmp);
	return (head);
}

// }
// 	head = NULL;
// 	last = NULL;
// 	while (tmp)
// 	{
// 		cmd = parse_cmd(tmp);
// 		if (!cmd)
// 		{
// 			free_all_cmds(head);
// 			return (NULL);
// 		}
// 		if (!head)
// 			head = cmd;
// 		else
// 			last->next = cmd;
// 		last = cmd;
// 		while (tmp && tmp->type != TOKEN_PIPE)
// 			tmp = tmp->next;
// 		if (tmp)
// 			tmp = tmp->next;
// 	}
// 	return (head);
// }
