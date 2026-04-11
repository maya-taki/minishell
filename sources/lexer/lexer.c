/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loena <loena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 19:11:10 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/04/10 20:42:26 by loena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int is_operator(char c)
{
	return (c == '|' || c == '&' || c == '<' || c == '>');	
}

int is_space(char c)
{
	return (c == '/t' || c == ' ' || c == '/v');
}

void	*read_input_redir(t_token **head, char *input, int *i)
{
	if (input[*i + 1] == '<')
	{
		add_token(head, new_token(TOKEN_HEREDOC, ft_strdup("<<")));
		*i += 2;
	}
}

void	add_token()

t_token	*lexer(char *input, int i)
{
	
	t_token	*token;

	if (!check_input(input)) //TODO
		return (NULL);
	token = NULL;
	
	return (token);
}

	// WORD,
	// PIPE,
	// REDIR_IN,
	// REDIR_OUT,
	// REDIR_APPEND,
	// HEREDOC,
	// SINGLE_QUOTE,
	// DOUBLE_QUOTE,
	// VAR,
	// AND,
	// OR,
