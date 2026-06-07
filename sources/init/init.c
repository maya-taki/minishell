/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osousa-d <osousa-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 19:35:32 by osousa-d          #+#    #+#             */
/*   Updated: 2026/06/06 19:24:11 by osousa-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"
 
static t_env	*init_env(char **envp);
static void		init_shell_values(t_shell *shell);
 
int	init_shell(t_shell *shell, char **envp)
{
	init_shell_values(shell);
	if (!(shell->env = init_env(envp)))
	{
		free_shell(shell);
		return (0);
	}
	return (1);
}
 
static t_env	*init_env(char **envp)
{
	t_env	*current;
	t_env	*head;
	int		i;
 
	i = 0;
	head = NULL;
	while (envp[i])
	{
		current = create_env_node(envp[i]);
		if (!current)
		{
			free_env_list(head);
			return (NULL);
		}
		env_add_back(&head, current);
		i++;
	}
	return (head);
}
 
t_cmd	*init_cmd(void)
{
	t_cmd	*cmd;
 
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->expanded_args = NULL;
	cmd->args = NULL;
	cmd->path = NULL;
	cmd->builtin = NONE;
	cmd->redirs = NULL;
	cmd->next = NULL;
	return (cmd);
}
 
static void	init_shell_values(t_shell *shell)
{
	shell->env = NULL;
	shell->cmd = NULL;
	shell->tokens = NULL;
	shell->input = NULL;
	shell->prompt_str = NULL;
	shell->exit_code = 0;
	shell->exit_shell = 0;
	shell->std_in = STDIN_FILENO;
	shell->std_out = STDOUT_FILENO;
}
 
t_token	*init_token(t_token_type type, char *value)
{
	t_token	*token;
 
	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	if (value)
		token->value = ft_strdup(value);
	else
		token->value = NULL;
	token->next = NULL;
	return (token);
}
