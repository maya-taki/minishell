/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 19:11:10 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/05/14 17:04:49 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

static int	is_input_valid(char *input)
{
	if (is_operator_valid(input) != 0 || were_quotes_closed(input) != 0)
		return (1);
	return (0);
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
		ft_printf(G"value: %s \ntype: %d\n"RST, token->value, token->type);
	}
	return (head);
}

t_token	*lexer(char *input)
{
	char		*trimmed;
	t_token		*tokens;

	if (!input)
		return (NULL);
	trimmed = ft_strtrim(input, " \r\t");
	if (!trimmed)
		return (NULL);
	if (is_input_valid(trimmed) != 0)
	{
		ft_printf(RED"Invalid command\n"RST);
		free(trimmed);
		return (NULL);
	}
	tokens = tokenize_input(trimmed);
	free(trimmed);
	return (tokens);
}
