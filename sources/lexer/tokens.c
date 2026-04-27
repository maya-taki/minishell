/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 18:25:55 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/04/27 19:00:50 by mtakiyos         ###   ########.fr       */
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

t_token_type	id_token_type(char *str, int *i)
{
	if (str[*i] == '|')
		return (TOKEN_PIPE);
	else if (str[*i] == '>')
	{
		if (str[*i + 1] == '>')
		{
			(*i)++;
			return (TOKEN_REDIR_APPEND);
		}
		else
			return (TOKEN_REDIR_OUT);
	}
	else if (str[*i] == '<')
	{
		if (str[*i + 1] == '<')
		{
			(*i)++;
			return (TOKEN_HEREDOC);
		}
		else
			return (TOKEN_REDIR_IN);
	}
	else
		return (TOKEN_WORD);
}

t_token	*next_token(char *input, int *i)
{
	t_token_type	type;
	t_token			*token;
	char			*value;
	
	type = id_token_type(input, i);
	if (type != TOKEN_WORD)
	{
		token = new_token(type, NULL);
		(*i)++;
	}
	else
	{
		value = handle_word(input, i);
		if (!value)
			return (NULL);
		token = new_token(type, value);
		free(value);
	}
	return (token);
}

void	free_tokens(t_token *tokens)
{
	t_token	*tmp;
	
	while (tokens->next)
	{
		tmp = tokens->next;
		free(tokens->value);
		free(tokens);
		tokens = tmp;
	}
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
