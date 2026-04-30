/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_inputs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 14:46:09 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/04/30 19:33:57 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

// if invalid_operator == 1 && state == quote_none
// return syntax error

char	*handle_word(char *input, int *i)
{
	int				start;
	char			*word;
	t_quote_state	state;

	state = QUOTE_NONE;
	start = *i;
	while (input[*i])
	{
		update_quote_state(input[*i], &state);
		if (state == QUOTE_NONE && (is_space(input[*i]) || is_operator(input[*i])))
			break ;
		(*i)++;
	}
	word = ft_substr(input, start, *i - start);
	if (!word)
		return (NULL);
	return (word);
}
