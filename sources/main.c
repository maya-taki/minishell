/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osousa-d <osousa-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 18:09:20 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/06/06 22:16:13 by osousa-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	(void)argc;
	(void)argv;

	if (!init_shell(&shell, envp))
		return (1);
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
			free(shell.input);
			continue ;
		}
		shell.cmd = parser(&shell);
		expand_all(shell.cmd, &shell);
		if (shell.cmd)
			shell.exit_code = execute(&shell);
		if (shell.tokens)
		{
			free_tokens(shell.tokens);
			shell.tokens = NULL;
		}
		if (shell.cmd)
		{
			free_all_cmds(shell.cmd);
			shell.cmd = NULL;
		}
		free_ptr((void **)&shell.input);
		if (shell.exit_shell)
			break ;
	}
	clear_history();
	free_shell(&shell);
	return (shell.exit_code);
}
