/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 16:35:01 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/04/30 19:29:55 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int	is_operator(char c)
{
	return (c == '|' || c == '>' || c == '<');
}

// if invalid_operator == 1 && state == quote_none
// return syntax error

int	is_invalid_operator(char *c)
{
	t_quote_state	state;
	int				i;
	
	state = QUOTE_NONE;
	i = 0;
	while (c[i])
	{
		update_quote_state(c[i], &state);
		if (c[i] == '|' && C[i + 1] == '|')
			return (1);
		else if (c[i] == '&')
			return (1);
		i++;
	}
	return (0);
}

int	is_space(char c)
{
	return (c == ' ' || c == '\n' || c == '\t');
}

void	update_quote_state(char c, t_quote_state *state)
{
	if (c == '\'' && *state == QUOTE_NONE)
		*state = QUOTE_SINGLE;
	else if (c == '\'' && *state == QUOTE_SINGLE)
		*state = QUOTE_NONE;
	else if (c == '"' && *state == QUOTE_NONE)
		*state = QUOTE_DOUBLE;
	else if (c == '"' && *state == QUOTE_DOUBLE)
		*state = QUOTE_NONE;
}

int		were_quotes_closed(char *input)
{
	t_quote_state	state;
	int				i;

	i = 0;
	state = QUOTE_NONE;
	while (input[i])
	{
		update_quote_state(input[i], &state);
		i++;
	}
	if (state == QUOTE_NONE)
		return (1);
	return (0);
}

//TODO: if invalid operator && outside quotes, return syntax error