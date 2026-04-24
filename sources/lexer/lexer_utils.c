/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loena <loena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 16:35:01 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/04/24 14:07:11 by loena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int	is_operator(char c)
{
	return (c == '|' || c == '>' || c == '<');
}

int	invalid_operator(char *c, int i)
{
	while (c[i])
	{
		if (c[i] == '|')
		{
			if (c[i + 1] == '|')
				return (1);
		}
		else if (c[i] == '&')
			return (1);
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
