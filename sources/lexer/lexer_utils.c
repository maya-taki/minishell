/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 16:35:01 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/04/17 20:05:02 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int	invalid_operator(char *c, int i)
{
	if ((c[i] == '|') || (c[i] == '|' && c[i + 1] == '|'))
		return (1);
	if ((c[i] == '&') || (c[i] == '&' && c[i + 1] == '&'))
		return (1);
	return (0);
}

int	is_quote(t_token **head, char *input, int *i)
{
	if (input[*i] == '"')
	{
		add_token(head, new_token(TOKEN_DOUBLE_QUOTE, '"'));
		(*i) += 1;
	}
	else if (input[*i] == '\'')
	{
		add_token(head, new_token(TOKEN_SINGLE_QUOTE, '\''));
		(*i) += 1;
	}
}

int	skip_spaces(char *input, int *i)
{
	while (input[*i] && (input[*i] == ' '))
		(*i)++;
	return (*i);
}
// int	is_invalid(char c)
// {
// 	return (c == ';');
// }