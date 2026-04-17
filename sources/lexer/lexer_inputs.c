/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_inputs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 14:46:09 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/04/16 21:59:06 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

char	*read_input_error()
{
	return (printf("syntax error\n"), NULL);
}


void	read_input_redir_in(t_token **head, char *input, int *i)
{
	if (input[*i + 1] == '<')
	{
		add_token(head, new_token(TOKEN_HEREDOC, "<<"));
		*i += 2;
	}
	else
	{
		add_token(head, new_token(TOKEN_REDIR_IN, "<"));
		(*i) += 1;
	}
}

void	read_input_redir_out(t_token **head, char *input, int *i)
{
	if (input[*i + 1] == '>')
	{
		add_token(head, new_token(TOKEN_REDIR_APPEND, ">>"));
		*i += 2;
	}
	else
	{
		add_token(head, new_token(TOKEN_REDIR_OUT, ">"));
		(*i) += 1;
	}
}

void	read_input_word(t_token **head, char *input, int *i)
{
	(*i) += ft_strlen(input);
	add_token(head, new_token(TOKEN_WORD, input));
}

void	handle_inputs(t_token *tokens, char *input, int *i)
{
	if (!input)
		return ;
	if (input[*i] == '>')
		read_input_redir_out(&tokens, input, i);
	else if (input[*i] == '<')
		read_input_redir_in(&tokens, input, i);
	else if (input[*i] == '|' || input[*i] == '&')
		read_input_error();
	else
		read_input_word(&tokens, input, i);
}
