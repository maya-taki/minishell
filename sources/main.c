/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osousa-d <osousa-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 18:09:20 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/05/08 16:46:07 by osousa-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// adaptando a main para os testes do executor

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_shell	*shell;
	char	*input;

	init_shell(&shell, envp);
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
			break;
		shell->cmd = init_cmd(input);

		execute(shell);
		free(input);
	}
	return (0);
}
