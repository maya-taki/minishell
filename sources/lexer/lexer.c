/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 19:11:10 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/06/04 22:40:27 by mtakiyos         ###   ########.fr       */
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
		{
			i++;
			continue ;
		}
		token = read_token(input, &i);
		if (!token)
		{
			free_tokens(head);
			return (NULL);
		}
		add_token(&head, token);
	}
	return (head);
}

t_token	*lexer(char *input)
{
	t_token		*tokens;

	if (!input)
		return (NULL);
	if (is_input_valid(input) != 0)
	{
		ft_printf(RED"minishell: command not allowed\n"RST);
		// free(input);
		return (NULL);
	}
	tokens = tokenize_input(input);
	// free(input);,0
	return (tokens);
}
