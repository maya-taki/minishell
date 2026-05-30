/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 21:44:06 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/05/29 20:22:11 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

int	expand_all(t_cmd *cmds, t_shell *shell)
{
	t_cmd	*cur;

	if (!shell)
		return (1);
	cur = cmds;
	while (cur)
	{
		if (expand_args(cur, shell) != 0)
			return (ERR_MALLOC);
		if (expand_redirs(cur, shell) != 0)
			return (ERR_MALLOC);
		cur = cur->next;
	}
	return (0);
}

int	expand_args(t_cmd *cmd, t_shell *shell)
{

}

int	expand_redirs(t_cmd *cmd, t_shell *shell)
{

}

char	*expand_word(const char *src, t_shell *shell)
{
	
}

char	*get_env_value(t_env *env, const char *name)
{
	
}