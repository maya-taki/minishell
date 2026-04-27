/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 18:09:20 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/04/27 19:52:29 by mtakiyos         ###   ########.fr       */
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
		tokens = lexer(mini.input, 0);
		if (*mini.input != '\0')
			add_history(mini.input);
		free(tokens);
	}
	clear_history();
	return (OK);
}
