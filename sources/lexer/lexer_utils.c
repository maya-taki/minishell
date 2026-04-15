/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 16:35:01 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/04/15 20:08:55 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int	is_operator(char c)
{
	return (c == '|' || c == '&' || c == '<' || c == '>');
}

int	skip_spaces(char *input, int *i)
{
	while (input[*i] && (input[*i] == ' '))
		(*i)++;
	return (*i);
}
int	is_quote(char c)
{
	return (c == '"' || c == '\'');
}

