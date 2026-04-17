/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 19:11:10 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/04/17 19:29:40 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

t_token	*new_token(t_token_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = ft_strdup(value);
	token->next = NULL;
	return (token);
}

void	add_token(t_token **head, t_token *new)
{
	t_token	*tmp;

	if (!(*head))
		*head = new;
	tmp = *head;
	(*head)->next = new;
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	tmp->next = new;
}

t_token	*lexer(char *input)
{
	t_token	*tokens;
	//char	*space;
	int		i;

	i = 0;
	tokens = malloc(sizeof(t_token));
	while (input[i] != '\0')
	{
		//if (!is_quote())
		//space = ft_strtrim(input, " \t\r\n");
		// if (space)
		// 	input++;
		if (invalid_operator(input, i))
			return (NULL);
		handle_inputs(tokens, input, &i);
	}
	return (tokens);
}

//esquece || e &&