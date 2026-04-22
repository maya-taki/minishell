/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osousa-d <osousa-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 18:09:20 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/04/22 11:44:43 by osousa-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// adaptando a main para os testes do executor
t_builtin get_builtin(char *arg)
{
	if (ft_strcmp(arg, "echo") == 0)
		return (ECHO);
	if (ft_strcmp(arg, "cd") == 0)
		return (CD);
	if (ft_strcmp(arg, "pwd") == 0)
		return (PWD);
	else
		return (NONE);
}

void	free_args(char **args)
{
	int	i;

	if (!args)
		return ;
	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

void	free_cmd(t_cmd *cmd)
{
	if (!cmd)
		return;
	if (cmd->args)
		free_args(cmd->args);
	free(cmd);
}

int main(void)
{
	t_cmd	*cmd;
	char	*input;

	while (1)
	{
		input = readline("minishell> ");
		if (!input)
			break;
		cmd = malloc(sizeof(t_cmd));
		if (!cmd)
			return (1);
		cmd->args = ft_split(input, ' ');
		if (!cmd->args || !cmd->args[0])
		{
			free_cmd(cmd);
			free(input);
			continue;
		}
		cmd->builtin = get_builtin(cmd->args[0]);
		execute(cmd);
		free_cmd(cmd);
		free(input);
	}
	return (0);
}
