/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 19:11:10 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/04/27 19:51:36 by mtakiyos         ###   ########.fr       */
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
	head = NULL;
	res = ft_strtrim(input, " \r\t");
	while (res[i])
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
	ft_printf("%d\n", tokens->type);
	return (head);
}
