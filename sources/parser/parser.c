/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 19:00:55 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/04/23 19:30:36 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// void	set_mini_args(t_mini *mini)
// {
// 	mini->tokens= NULL;;
// 	mini->cmd = NULL;
// 	mini->input = NULL;
// }

//TODO: verify unclosed/closed quotes
//TODO: verify strange || and && behavior

static int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

int		verify_syntax(t_mini *mini)
{
	int	i;
	int	quote_counter;
	t_token *tokens;
	
	quote_counter = 0;
	i = 0;
	tokens = lexer(mini->input);
	if (!tokens)
		return (NULL);
	while (tokens)
	{	
		if (invalid_operator(tokens, i))
			return (NULL);
		if (is_quote(&tokens[i]) == 1)
		{
			ft_printf("test\n");
			quote_counter = 1;
		}
		i++;
	}
	i = 0;
}
