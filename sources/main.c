/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 18:09:20 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/06/05 04:48:34 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_shell	shell;

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
			free(shell.tokens);
			continue ;
		}
		shell.cmd = parser(&shell); //TODO
		expand_all(shell.cmd, &shell);
		if (shell.cmd)
			shell.exit_code = execute(&shell);
		if (shell.exit_shell)
			break ;
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
	}
	clear_history();
	free_shell(&shell);
	return (0);
}
