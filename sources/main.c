/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 18:09:20 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/06/08 23:12:56 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void proper_exit(t_shell *shell)
{
	ft_printf("exit\n");
	free_all_cmds(shell->cmd);
	free_env_list(shell->env);
	close(shell->std_in);
	close(shell->std_out);
	exit(0);
}

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
		setup_signals();
		shell.input = readline("minishell> ");
		if (g_signal == 130)
		{
			shell.exit_code = 130;
			g_signal = 0;
			free(shell.input);
			continue ;
		}
		if (!shell.input)
			proper_exit(&shell);
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
} //TODO
