/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 14:38:01 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/05/27 22:00:56 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

t_cmd	*new_cmd(void);
int		count_words(t_token *token);
int		count_cmds(t_token *token_list);
int		open_file(int *fd_ptr, char *path, int flags);

t_cmd	*new_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->path = NULL;
	cmd->redirs = NULL;
	cmd->next = NULL;
	// cmd->builtin = BUILTIN_NONE; //TODO
	return (cmd);
}

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

void	debug_print_cmds(t_cmd *cmds)
{
	int		i;
	t_redir	*r;
	int		cmd_index;

	cmd_index = 1;
	while (cmds)
	{
		printf(C"=== CMD %d ===\n", cmd_index++);
		i = 0;
		if (cmds->args)
		{
			while (cmds->args[i])
			{
				printf("  arg[%d]: %s\n", i, cmds->args[i]);
					i++;
			}
		}
		r = cmds->redirs;
		while (r)
		{
			printf("  redir type %d -> %s\n"RST, r->type, r->file);
			r = r->next;
		}
		cmds = cmds->next;
	}
}
