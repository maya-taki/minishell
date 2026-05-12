/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 22:29:37 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/05/11 19:35:34 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

int	validate_syntax(t_token *tokens)
{
	t_token	*tmp;
	
	tmp = tokens;
	if (!tmp)
		return (0);
	if (tmp->type == TOKEN_PIPE)
		return (0);
	while (tmp)
	{
		if (is_redir(tmp) && (!tmp->next || tmp->next->type != TOKEN_WORD))
			return (0);
		if (tmp->type == TOKEN_PIPE && tmp->next
			&& tmp->next->type == TOKEN_PIPE)
			return (ERR_SYNTAX);
		tmp = tmp->next;
	}
	return (1);
}
