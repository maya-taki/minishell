/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 22:29:37 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/05/08 21:30:42 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

int	validate_syntax(t_token *tokens)
{
	t_token	*tmp;
	
	tmp = tokens;
	if (!tmp)
		return (1);
	if (tmp->type == TOKEN_PIPE)
		return (ERR_SYNTAX);
	while (tmp)
	{
		if (!tmp->next && tmp->type != TOKEN_WORD)
			return (ERR_SYNTAX);
		if (tmp->type == TOKEN_PIPE && tmp->next->type == TOKEN_PIPE)
			return (ERR_SYNTAX);
		tmp = tmp->next;
	}
	return (1);
}