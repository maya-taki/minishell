/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 18:09:20 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/04/16 21:58:42 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	main(void)
{
	t_mini	mini;

	using_history();
	while (1)
	{
		mini.input = readline("> ");
		lexer(mini.input);
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
