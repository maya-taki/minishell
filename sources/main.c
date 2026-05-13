/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 18:09:20 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/05/12 22:41:16 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"


int	main(void)
{
	t_mini	mini;

	using_history();
	while (1)
	{
		mini.input = readline("Minishell$ ");
		mini.tokens = lexer(mini.input);
		add_history(mini.input);
		mini.cmd = parser(&mini);
		if (!mini.cmd)
		{
			free_tokens(mini.tokens);
			continue ;
		}
		if (mini.tokens != NULL)
			free(mini.input);
		free(mini.tokens);
	}
	clear_history();
	return (0);
}
