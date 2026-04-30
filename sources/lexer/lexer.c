/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 19:11:10 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/04/30 19:37:28 by mtakiyos         ###   ########.fr       */
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
	res = ft_strtrim(input, " \r\t");
	if (!res)
		return (NULL);
	i = 0;
	if (!were_quotes_closed(res) || is_invalid_operator(res))
	{
		free(res);
		return (NULL);
	}
	head = NULL;
	while (res[i])
	{
		if (res[i] && is_space(res[i]))
			i++;
		if (!res[i])
			break ;
		tokens = read_token(res, &i);
		if (!tokens)
		{
			free_tokens(head);
			free(res);
			return (NULL);
		}
		add_token(&head, tokens);
		ft_printf(G"%d\n%s\n"RST, tokens->type, tokens->value);
	}
	free(res);
	return (head);
}


// if (!is_inside_quotes(res, 0) && is_operator(res[i]));