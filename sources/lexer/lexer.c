/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 19:11:10 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/05/02 19:45:17 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

static int	validate_input(char *input)
{
	if (!were_quotes_closed(input))
		return (0);
	if (is_invalid_operator(input))
		return (0);
	return (1);
}

static t_token	*tokenize_input(char *input)
{
	t_token	*head;
	t_token	*token;
	int		i;

	head = NULL;
	i = 0;
	while (input[i])
	{
		if (is_space(input[i]))
			i++;
		token = read_token(input, &i);
		if (!token)
		{
			free_tokens(head);
			return (NULL);
		}
		add_token(&head, token);
		ft_printf(G"type: %d\nvalue: %s\n"RST, token->type, token->value);
	}
	return (head);
}

t_token	*lexer(char *input)
{
	char	*trimmed;
	t_token	*tokens;

	if (!input)
		return (NULL);
	trimmed = ft_strtrim(input, " \r\t");
	if (!trimmed)
		return (NULL);
	if (!validate_input(trimmed))
	{
		ft_printf("syntax error\n");
		free(trimmed);
		return (NULL);
	}
	tokens = tokenize_input(trimmed);
	free(trimmed);
	return (tokens);
}
