/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_inputs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 14:46:09 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/05/02 15:40:04 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

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
