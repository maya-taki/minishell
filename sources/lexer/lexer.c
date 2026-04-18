/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 19:11:10 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/04/18 19:17:37 by mtakiyos         ###   ########.fr       */
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

void	print_tokens(t_token *head)
{
	t_token	*temp;

	if (!head)
		return ;
	temp = head;
	if(temp != NULL)
	{
		printf(G"Value: %s\nType: %d\n"RST, temp->value, temp->type);
		temp = temp->next;
	}
}

t_token	*lexer(char *input)
{
	t_token	*tokens;
	char	*tmp;
	int		i;

	i = 0;
	tmp = ft_strtrim(input, " \r\t");
	tokens = malloc(sizeof(t_token));
	while (input[i] != '\0')
	{
		while (is_space(tmp[i]) == 1)
			i++;
		if (invalid_operator(input, i))
			return (NULL);
		if (is_operator(tmp[i]))
			handle_operator(tokens, input, &i);
		else
			handle_word(&tokens, input, &i);
	}
	free(tmp);
	return (tokens);
}

// if (!quote) && 