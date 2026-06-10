/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 00:16:40 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/06/10 03:29:53 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"
#include <termios.h>

void	proper_exit(t_shell *shell)
{
	ft_printf("exit\n");
	free_all_cmds(shell->cmd);
	free_env_list(shell->env);
	close(shell->std_in);
	close(shell->std_out);
	exit(0);
}

static int	prepare_cycle(t_shell *shell)
{
	setup_signals();
	shell->input = readline("minishell> ");
	if (!shell->input)
		return (-1);
	if (g_signal == 130)
	{
		shell->exit_code = 130;
		g_signal = 0;
		free_ptr((void **)&shell->input);
		return (0);
	}
	add_history(shell->input);
	return (1);
}

static void	exec_cycle(t_shell *shell)
{
	shell->tokens = lexer(shell->input);
	if (!shell->tokens)
		return ;
	shell->cmd = parser(shell);
	expand_all(shell->cmd, shell);
	if (shell->cmd)
		shell->exit_code = execute(shell);
}

static int	shell_cycle(t_shell *shell, struct termios *term)
{
	int	status;

	status = prepare_cycle(shell);
	if (status != 1)
	{
		tcsetattr(STDIN_FILENO, TCSANOW, term);
		return (status);
	}
	exec_cycle(shell);
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
	t_shell			shell;
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
