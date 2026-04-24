/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loena <loena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 19:11:10 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/04/24 14:47:29 by loena            ###   ########.fr       */
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

// void	print_tokens(t_token *head)
// {
// 	t_token	*temp;

// 	if (!head)
// 		return ;
// 	temp = head;
// 	if(temp != NULL)
// 	{
// 		printf(G"Value: %s\nType: %d\n"RST, temp->value, temp->type);
// 		temp = temp->next;
// 	}
// }

static int	is_quote_closed(char *input, int i)
{
	int counter;

	counter = 0;
	while (input[i])
	{
		if (input[i] == '"')
			counter++;
		i++;
	}
	if (counter % 2 == 0) //is quote closed? 
		return (1);
	else
		return (0);
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
		if (!is_quote_closed(input, 0) && invalid_operator(input, 0)) //TODO: needs to activate only if outside quotes
			return (NULL);
		if (is_operator(tmp[i]))
			handle_operator(tokens, input, &i);
		else
			handle_word(&tokens, input, &i);
		i++;
	}
	ft_printf(G"%s\n"RST, input);
	free(tmp);
	return (tokens);
}
