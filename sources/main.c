/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 18:09:20 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/05/11 22:44:26 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int	main(void)
{
	t_mini	mini;
	t_token	*tokens;

	using_history();
	while (1)
	{
		mini.input = readline("Minishell$ ");
		tokens = lexer(mini.input);
		mini.cmd = parser(&mini);
		if (!mini.cmd)
		{
			free_all_cmds(mini.cmd);
			return (0);
		}
		if (*mini.input != '\0')
			add_history(mini.input);
		free(tokens);
	}
	clear_history();
	return (0);
}
