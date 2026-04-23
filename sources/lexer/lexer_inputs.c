/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_inputs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 14:46:09 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/04/23 20:43:30 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

static void	read_input_redir_out(t_token **head, char *input, int *i)
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

static void	read_input_redir_in(t_token **head, char *input, int *i)
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

static void	read_input_pipe(t_token **head, int *i)
{
	add_token(head, new_token(TOKEN_REDIR_OUT, "|"));
	(*i) += 1;
}

void	handle_word(t_token **head, char *input, int *i)
{
	int		start;
	int		in_single;
	int		in_double;
	char	*word;
	
	in_single = 0;
	in_double = 0;
	start = *i;
	while ((input[*i]) && (in_single || in_double
			|| !is_operator(input[*i])
			|| !is_space(input[*i])))
	{
		if (input[*i] == '\'' && !in_double)
			in_single = !in_single;
		if (input[*i] == '"' && !in_single)
			in_double = !in_double;
		(*i)++;
	}
	word = ft_substr(input, start, *i - start);
	if (!word)
		return ;
	add_token(head, new_token(TOKEN_WORD, word));
}

void	handle_operator(t_token *tokens, char *input, int *i)
{
	if (!input)
		return ;
	if (input[*i] == '>')
		read_input_redir_out(&tokens, input, i);
	else if (input[*i] == '<')
		read_input_redir_in(&tokens, input, i);
	else if (input[*i] == '|')
		read_input_pipe(&tokens, i);
}
