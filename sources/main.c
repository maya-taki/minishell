/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 18:09:20 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/04/17 18:55:37 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	main(void)
{
	t_mini	mini;
	t_token	*tokens;	
	
	using_history();
	while (1)
	{
		mini.input = readline("> ");
		tokens = lexer(mini.input);
		if (!tokens)
		{
			printf(RED"%s"RST, "[ERROR] Syntax Error.\n");
			continue ;
		}
		if (!mini.input)
			break ;
		if (*mini.input != '\0')
			add_history(mini.input);
		printf("%s\n", mini.input);
		free(mini.input);
	}
	clear_history();
	return (OK);
}
