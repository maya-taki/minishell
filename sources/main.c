/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osousa-d <osousa-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 18:09:20 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/05/17 19:30:03 by osousa-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

// ESSE TERIA DE SER NOSSO FLUXO DA MAIN
int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_shell	shell;

	init_shell(&shell, envp); // frees tratados
	// daqui pra baixo tem que revisar todo o código;
	using_history();
	while (1)
	{
		shell.input = readline("minishell> ");
		if (!shell.input)
			break ;

		add_history(shell.input);

		shell.tokens = lexer(shell.input);
		shell.cmd = parser(&shell); // tratar os frees do init_cmd

		if (shell.cmd)
			execute(&shell);

		free_all(&shell); // fazer função que limpa tudo
	}
	clear_history();
	return (0);
}
