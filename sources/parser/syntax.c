/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 22:29:37 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/05/26 16:56:49 by mtakiyos         ###   ########.fr       */
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

int	is_quoted(char *delimiter)
{
	if (!delimiter)
		return (0);
	if (delimiter[0] == '\'' || delimiter[0] == '"')
		return (1);
	return (0);
}

int	unclosed_quote(char *delimiter)
{
	int	single_quote;
	int	double_quote;
	int	i;

	i = 0;
	single_quote = 0;
	double_quote = 0;
	while (delimiter[i])
	{
		if (delimiter[i] == '\'')
			single_quote++;
		if (delimiter[i] == '"')
			double_quote++;
		i++;
	}
	if (single_quote == 1 || double_quote == 1)
		return (print_error("quote")); //TODO
	return (1);
}
