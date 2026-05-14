/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 22:29:37 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/05/14 19:10:06 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

static int	is_pipe_last(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		if (!tmp->next && tmp->type == TOKEN_PIPE)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	validate_syntax(t_token *tokens)
{
	t_token	*tmp;
	
	tmp = tokens;
	if (!tmp)
		return (1);
	if (tmp->type == TOKEN_PIPE)
		return (ERR_SYNTAX);
	if (is_pipe_last(tmp) != 0)
		return (ERR_SYNTAX);
	while (tmp)
	{
		if (is_redir(tmp) && (!tmp->next || tmp->next->type != TOKEN_WORD))
			return (ERR_SYNTAX);
		if (tmp->type == TOKEN_PIPE && tmp->next
			&& tmp->next->type == TOKEN_PIPE)
			return (ERR_SYNTAX);
		tmp = tmp->next;
	}
	return (0);
}
