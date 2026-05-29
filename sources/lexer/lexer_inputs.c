/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_inputs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 14:46:09 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/05/29 14:13:29 by mtakiyos         ###   ########.fr       */
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
		if (state == QUOTE_NONE && (is_space(input[*i])
				|| is_operator(input[*i])))
			break ;
		(*i)++;
	}
	word = ft_substr(input, start, *i - start);
	if (!word)
		return (NULL);
	return (word);
}

t_token	*handle_operator(t_token_type type, char *input, int *i)
{
	int		len;
	char	*value;
	t_token	*token;

	len = 1;
	if (type == TOKEN_HEREDOC || type == TOKEN_REDIR_APPEND)
		len = 2;
	value = ft_substr(input, *i, len);
	if (!value)
		return (NULL);
	token = init_token(type, value);
	free(value);
	if (len == 2)
		(*i)++;
	(*i)++;
	return (token);
}
