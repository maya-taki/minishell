/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otton-sousa <otton-sousa@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 18:09:20 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/05/18 00:24:14 by otton-sousa      ###   ########.fr       */
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
	using_history();
	while (1)
	{
		shell.input = readline("minishell> ");
		if (!shell.input)
			break ;
		add_history(shell.input);
		shell.tokens = lexer(shell.input);
		shell.cmd = parser(&shell);
		if (shell.cmd)
			execute(&shell); // Fazer os builtin pwd, cd (ambos usando a env)
		free_all(&shell); // fazer função que limpa tudo
	}
	clear_history();
	return (0);
}
