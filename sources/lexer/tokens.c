/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 18:25:55 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/05/27 21:55:34 by mtakiyos         ###   ########.fr       */
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
	if (value)
		token->value = ft_strdup(value);
	else
		token->value = NULL;
	token->next = NULL;
	return (token);
}

void	add_token(t_token **head, t_token *new_token)
{
	t_token	*current;

	if (!head || !new_token)
		return ;
	if (*head == NULL)
	{
		*head = new_token;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_token;
}

t_token_type	id_token_type(char *c, int *i)
{
	if (c[*i] == '|')
		return (TOKEN_PIPE);
	else if (c[*i] == '>')
	{
		if (c[*i + 1] == '>')
			return (TOKEN_REDIR_APPEND);
		else
			return (TOKEN_REDIR_OUT);
	}
	else if (c[*i] == '<')
	{
		if (c[*i + 1] == '<')
			return (TOKEN_HEREDOC);
		else
			return (TOKEN_REDIR_IN);
	}
	else
		return (TOKEN_WORD);
}

t_token	*read_token(char *input, int *i)
{
	t_token_type	type;
	t_token			*token;
	char			*value;

	type = id_token_type(input, i);
	if (type != TOKEN_WORD)
		return (handle_operator(type, input, i));
	else
	{
		value = handle_word(input, i);
		if (!value)
			return (NULL);
		token = new_token(type, value);
		free(value);
		return (token);
	}
}
