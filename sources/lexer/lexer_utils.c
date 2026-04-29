/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 16:35:01 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/04/28 20:59:01 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int	is_operator(char c)
{
	return (c == '|' || c == '>' || c == '<');
}

int	invalid_operator(char *c, int i)
{
	while (c[i])
	{
		if (c[i] == '|')
		{
			if (c[i + 1] == '|')
				return (1);
		}
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

//TODO: make a function to determine if operator is inside or outside quotes

// void	is_inside_quotes(char *c, int i, int double_quote, int single_quote)
// {
// 	while (c[i])
// 	{
// 		if (c[i] == '\'' || c[i] == '"')
// 		{
// 			if (c[i] == '\'')
// 				single_quote++;
// 			else
// 				double_quote++;
// 			i++;
// 		}
// 		if (c[i] == '\'' || c[i] == '"')
// 		{
// 			if (c[i] == '\'')
// 				single_quote--;
// 			else
// 				double_quote--;
// 			i++;
// 		}
// 	}
// 	if (single_quote == 0 || double_quote == 0)
// 		return (1);
// 	return (0);
// }

void	quote_state(char *c, t_quote_state *state)
{
	int	i;
	
	i = 0;
	while (c[i])
	{
		if (c[i] == '\'' && state != QUOTE_NONE)
			state = QUOTE_SINGLE;
		else if ()
		else if (c[i] == '"' && state != QUOTE_DOUBLE)
			state = QUOTE_DOUBLE;	
		
	}
}


//if operator is inside quotes, they don't act like operators, so I can just use an int to determine
//if quotes exist and if they are closed (1 if closed, 0 if no quotes, -1 if unclosed)

//TODO: if invalid operator && outside quotes, return syntax error