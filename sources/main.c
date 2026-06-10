/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 00:16:40 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/06/10 02:34:01 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"
# include <termios.h>

void	proper_exit(t_shell *shell)
{
	ft_printf("exit\n");
	free_all_cmds(shell->cmd);
	free_env_list(shell->env);
	close(shell->std_in);
	close(shell->std_out);
	exit(0);
}

static int manage_input(t_shell *shell, struct termios *term)
{
	shell->tokens = lexer(shell->input);
	if (!shell->tokens)
	{
		free(shell->input);
		shell->input = NULL;
		tcsetattr(STDIN_FILENO, TCSANOW, term);
		return (0);
	}
	shell->cmd = parser(shell);
	return (0);
}

static int	shell_cycle(t_shell *shell, struct termios *term)
{
	setup_signals();

	shell->input = readline("minishell> ");
	if (g_signal == 130)
	{
		shell->exit_code = 130;
		g_signal = 0;
		free(shell->input);
		shell->input = NULL;
		return (0);
	}
	if (!shell->input)
		return (-1);
	add_history(shell->input);
	manage_input(shell, term);
	expand_all(shell->cmd, shell);
	if (shell->cmd)
		shell->exit_code = execute(shell);
	if (shell->tokens)
	{
		free_tokens(shell->tokens);
		shell->tokens = NULL;
	}
	if (shell->cmd)
	{
		free_all_cmds(shell->cmd);
		shell->cmd = NULL;
	}
	free_ptr((void **)&shell->input);
	tcsetattr(STDIN_FILENO, TCSANOW, term);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	 t_shell		shell;
 	struct termios	term;

	(void)argc;
	(void)argv;
	tcgetattr(STDIN_FILENO, &term);
	if (!init_shell(&shell, envp))
		return (1);
	using_history();
	while (!shell.exit_shell)
		if (shell_cycle(&shell, &term) == -1)
			proper_exit(&shell);
	clear_history();
	free_shell(&shell);
	return (shell.exit_code);
}
