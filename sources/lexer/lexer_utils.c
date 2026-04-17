/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 16:35:01 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/04/17 19:31:12 by mtakiyos         ###   ########.fr       */
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