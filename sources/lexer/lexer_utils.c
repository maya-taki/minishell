/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 16:35:01 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/04/20 20:57:30 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int	is_operator(char c)
{
	return (c == '|' || c == '>' || c == '<');
}

int	invalid_operator(char *c, int i)
{
	if ((c[i] == '|' && c[i + 1] == '|'))
		return (1);
	if ((c[i] == '&' && c[i + 1] != '&') || (c[i] == '&' && c[i + 1] == '&'))
		return (1);
	return (0);
}

int	is_space(char c)
{
	return (c == ' ' || c == '\n' || c == '\t');
}
// int	is_invalid(char c)
// {
// 	return (c == ';');
// }

// int	is_quote(t_token **head, char *input, int *i)
// {
// 	if (input[*i] == '"')
// 	{
// 		add_token(head, new_token(TOKEN_DOUBLE_QUOTE, '"'));
// 		(*i) += 1;
// 	}
// 	else if (input[*i] == '\'')
// 	{
// 		add_token(head, new_token(TOKEN_SINGLE_QUOTE, '\''));
// 		(*i) += 1;
// 	}
// }

void	set_mini_args(t_mini *mini)
{
	mini->tokens= NULL;;
	mini->cmd = NULL;
	mini->input = NULL;
}

void	validate_argc(int ac, char **av)
{
	if ((ac =! 1) && av[1])
	{
		printf(RED"Invalid input. Correct usage: ./minishell\n"RST);
		exit(1);
	}
}