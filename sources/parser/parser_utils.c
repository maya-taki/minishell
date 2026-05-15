/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osousa-d <osousa-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 14:38:01 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/05/15 11:06:43 by osousa-d         ###   ########.fr       */
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
	cmd->cmd_path = NULL;
	cmd->redirs = NULL;
	cmd->next = NULL;
	return (cmd);
}

int	open_file(int *fd_ptr, char *path, int flags)
{
	if (*fd_ptr > 2)
		close(*fd_ptr);	
	*fd_ptr = open(path, flags, 0644);
	if (*fd_ptr == -1)
	{
		perror(path);
		return (1);
	}
	return (0);
}

int count_cmds(t_token *token_list)
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

int count_words(t_token *token)
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
