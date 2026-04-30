/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 19:11:10 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/04/29 19:49:16 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

t_token	*lexer(char *input, int i)
{
	t_token *head;
	t_token	*tokens;
	char	*res;

	if (!input)
		return (NULL);
	tokens = NULL;
	head = NULL;
	res = ft_strtrim(input, " \r\t");
	while (res[i])
	{
		if (validade_quotes(res) == 1)
		{
			while (is_space(res[i]) == 1)
				i++;
			if (!res[i])
				return (NULL);
			tokens = next_token(res, &i);
			if (!tokens)
			{
				free_tokens(tokens);
				return (NULL);
			}
			add_token(&head, tokens);
		}
		else
			return (NULL);
	}
	return (head);
}


// if (!is_inside_quotes(res, 0) && is_operator(res[i]));