/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loena <loena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 19:00:55 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/05/09 22:18:05 by loena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

int	fill_args(t_token *seg_start, t_cmd *cmd)
{
	int 	i;
	t_token *tmp;

	cmd->cmd_args = malloc(sizeof(char *) * (count_words(seg_start) + 1));
	if (!cmd->cmd_args)
		return (0);
	i = 0;
	tmp = seg_start;
	while (tmp && tmp->type != TOKEN_PIPE)
	{
		if (is_redir(tmp))
		{
			tmp = tmp->next;
			if (tmp)
				tmp = tmp->type;
			continue ;
		}
		if (tmp->type == TOKEN_WORD)
		{
			cmd->cmd_args[i] = ft_strdup(tmp->value);
			if (!cmd->cmd_args[i])
				return (0);
			i++;
		}
		tmp = tmp->next;
	}
	cmd->cmd_args[i] = NULL;
	return (1);
}
int	fill_redirs(t_token *seg_start, t_cmd *cmd)
{
	
}
