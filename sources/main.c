/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 18:09:20 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/05/14 21:52:00 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"


int	main(void)
{
	t_mini	mini;

	using_history();
	while (1)
	{
		mini.input = readline("Minishell$ ");
		mini.tokens = lexer(mini.input);
		add_history(mini.input);
		mini.cmd = parser(&mini);
		if (!mini.cmd)
		{
			free_tokens(mini.tokens);
			continue ;
		}
		if (mini.tokens != NULL)
			free(mini.input);
		free(mini.tokens);
	}
	clear_history();
	return (0);
}
// adaptando a main para os testes do executor

// int main(int argc, char **argv, char **envp)
// {
// 	(void)argc;
// 	(void)argv;
// 	t_shell	*shell;
// 	char	*input;

// 	init_shell(&shell, envp);
// 	while (1)
// 	{
// 		input = readline("minishell> ");
// 		if (!input)
// 			break;
// 		shell->cmd = init_cmd(input);
// 		execute(shell);
// 		free(input);
// 	}
// 	return (0);
// }
