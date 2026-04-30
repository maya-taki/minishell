/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_inputs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 14:46:09 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/04/29 21:01:37 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"


char	*handle_word(char *input, int *i)
{
	int		start;
	int		in_single;
	int		in_double;
	char	*word;
	
	in_single = 0;
	in_double = 0;
	start = *i;
	while ((input[*i]) && (in_single || in_double
			&& !is_operator(input[*i])
			&& !is_space(input[*i])))
	{
		if (input[*i] == '\'' && !in_double)
			in_single = !in_single;
		if (input[*i] == '"' && !in_single)
			in_double = !in_double;
		(*i)++;
	}
	word = ft_substr(input, start, *i - start);
	if (!word)
		return (NULL);
	return (word);
}
