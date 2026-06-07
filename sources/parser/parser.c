/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osousa-d <osousa-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 19:00:55 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/06/06 23:14:44 by osousa-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

static int	validate_parser(t_shell *shell)
{
	if (!shell || !shell->tokens)
		return (1);
	if (validate_syntax(shell->tokens) != 0)
	{
		handle_error(ERR_SYNTAX, NULL, "`newline'", 0);
		return (1);
	}
	return (0);
}

static t_cmd	*run_parse(t_cmd *cmd, t_token *tmp)
{
	t_cmd	*head;
	t_cmd	*last;

	head = NULL;
	last = NULL;
	while (tmp)
	{
		cmd = parser_handler(tmp);
		if (!cmd)
			return (free_all_cmds(head));
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
	t_token	*tmp;

	if (!shell || validate_parser(shell) != 0)
		return (NULL);
	cmd = NULL;
	tmp = shell->tokens;
	head = run_parse(cmd, tmp);
	//debug_print_cmds(head);
	return (head);
}
