/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 18:09:20 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/06/04 23:24:13 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	t_shell	shell;

	init_shell(&shell, envp);
	using_history();
	while (1)
	{
		shell.input = readline("minishell> ");
		if (!shell.input)
			break ;
		add_history(shell.input);
		shell.tokens = lexer(shell.input);
		if (!shell.tokens)
		{
			free(shell.tokens);
			break ;
		}
		shell.cmd = parser(&shell);
		if (shell.cmd)
			execute(&shell); // pwd nao ta pronto
		// free_all(&shell); // fazer função que limpa tudo
	}
	clear_history();
	return (0);
}
