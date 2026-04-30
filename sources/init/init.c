/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osousa-d <osousa-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 19:35:32 by osousa-d          #+#    #+#             */
/*   Updated: 2026/04/29 21:12:26 by osousa-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

// typedef struct s_cmd
// {
// 	char			**argv;
// 	t_builtin		builtin;
// 	t_redir			*redir;
// 	struct s_cmd	*next;
// }	t_cmd;

t_cmd	*init_cmd(char *input)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = ft_split(input, ' ');
	if (!cmd->args || !cmd->args[0])
	{
		free_cmd(cmd);
		return (NULL);
	}
	cmd->builtin = get_builtin(cmd->args[0]);
	return (cmd);
}

static t_env	*init_env(char **envp)
{
	t_env	*node_env;
	int		i;

	i = 0;
	while (envp[i])
	{
		node_env = malloc(sizeof(t_env));
		if (node_env)
			return (NULL);
			
		i++;
	}
	
	return (env);
}

t_shell	*init_shell(t_shell *shell, char **envp)
{
	
	shell->env = init_env(envp);
	
	// iniciar as variaveis da estrutura t_shell
	
}


