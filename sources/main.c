/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 18:09:20 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/04/23 20:44:14 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int	main(void)
{
	t_mini	mini;
	t_token	*tokens;	
	
	using_history();
	// validate_argc(ac, av);
	while (1)
	{
		mini.input = readline("> ");
		tokens = lexer(mini.input);
		// verify_syntax(lexer(tokens));
		if (!tokens)
		{
			printf(RED"%s"RST, "[ERROR] Syntax Error.\n");
			continue ;
		}
		if (!mini.input)
			break ;
		if (*mini.input != '\0')
			add_history(mini.input);
		//ft_printf("%s\n", mini.input);
		free(mini.input);
	}
	clear_history();
	return (OK);
}
