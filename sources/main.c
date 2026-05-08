/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 18:09:20 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/05/08 19:43:46 by mtakiyos         ###   ########.fr       */
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
		if (validate_syntax(tokens) != 1)
			return (ERR_NONE);
		if (*mini.input != '\0')
			add_history(mini.input);
		free(tokens);
	}
	clear_history();
	return (0);
}
