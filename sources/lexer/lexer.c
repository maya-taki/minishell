/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 19:11:10 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/04/11 20:59:31 by mtakiyos         ###   ########.fr       */
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


	if (!(*head)->value)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
	{
		printf("%d %s ADD TOKEN\n",new->type, new->value);
		tmp = tmp->next;
	}
	tmp->next = new;
	
}

t_token	*lexer(char *input)
{
	t_token	*tokens;
	int		i;
	
	i = 0;
	tokens = malloc(sizeof(t_token));
	handle_inputs(tokens, input, &i);
	return (tokens);
}
