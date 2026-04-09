/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 19:11:10 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/04/08 22:14:12 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"

int is_operator(char *tmp)
{
	
}

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