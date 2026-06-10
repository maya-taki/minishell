/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osousa-d <osousa-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 14:38:01 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/06/06 19:16:58 by osousa-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

int	count_cmds(t_token *token_list)
{
	int		len;
	t_token	*tmp;

	len = 1;
	tmp = token_list;
	while (tmp)
	{
		if (tmp->type == TOKEN_PIPE)
			len++;
		tmp = tmp->next;
	}
	return (len);
}

int	count_words(t_token *token)
{
	int		counter;
	t_token	*tmp;

	counter = 0;
	tmp = token;
	while (tmp && tmp->type != TOKEN_PIPE)
	{
		if (is_redir(tmp))
		{
			tmp = tmp->next;
			if (tmp)
				tmp = tmp->next;
			continue ;
		}
		if (tmp->type == TOKEN_WORD)
			counter++;
		tmp = tmp->next;
	}
	return (counter);
}

int	is_redir(t_token *token)
{
	return (token->type == TOKEN_HEREDOC
		|| token->type == TOKEN_REDIR_OUT
		|| token->type == TOKEN_REDIR_APPEND
		|| token->type == TOKEN_REDIR_IN);
}

void	set_builtin(t_cmd *cmd)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return ;
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		cmd->builtin = ECHO;
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		cmd->builtin = CD;
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		cmd->builtin = PWD;
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		cmd->builtin = EXPORT;
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		cmd->builtin = UNSET;
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		cmd->builtin = ENV;
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		cmd->builtin = EXIT;
	else
		cmd->builtin = NONE;
}

// void	debug_print_cmds(t_cmd *cmds)
// {
// 	int		i;
// 	t_redir	*r;
// 	int		cmd_index;

// 	cmd_index = 1;
// 	while (cmds)
// 	{
// 		ft_printf(C"=== CMD %d ===\n", cmd_index++);
// 		i = 0;
// 		if (cmds->args)
// 		{
// 			while (cmds->args[i])
// 			{
// 				ft_printf("  arg[%d]: %s\n", i, cmds->args[i]);
// 				i++;
// 			}
// 		}
// 		r = cmds->redirs;
// 		while (r)
// 		{
// 			ft_printf("  redir type %d -> %s\n", r->type, r->file);
// 			r = r->next;
// 		}
// 		cmds = cmds->next;
// 		ft_printf(RST);
// 	}
// }
