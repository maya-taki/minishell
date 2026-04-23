/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 16:35:01 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/04/23 20:57:31 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int	is_operator(char c)
{
	return (c == '|' || c == '>' || c == '<');
}

int	invalid_operator(char *c, int i)
{
	int	quote;

	quote = 1;
	while (c[i] && quote == 1)
	{
		if (c[i] == '"')
			quote *= -1;
		if (c[i] == '|' && quote == -1)
		{
			if (c[i + 1] == '|')
				return (1);
		}
		else if (c[i] == '&' && quote == -1)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

int	is_space(char c)
{
	return (c == ' ' || c == '\n' || c == '\t');
}

// void	validate_argc(int ac, char **av)
// {
// 	if ((ac =! 1) && av[1])
// 	{
// 		printf(RED"Invalid input. Correct usage: ./minishell\n"RST);
// 		exit(1);
// 	}
// }