/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 22:29:37 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/05/08 17:10:08 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

int	validate_syntax(t_token *token)
{
	t_token	*tmp;
	
	tmp = token;
	if (!tmp)
		return (ERR_NONE);
	if (tmp->type == TOKEN_PIPE)
		return (ERR_SYNTAX);
	while (tmp)
	{
		if (!tmp->next && tmp->next->type != TOKEN_WORD)
			return (ERR_SYNTAX);
		if (tmp->type == TOKEN_PIPE && tmp->next->type == TOKEN_PIPE)
			return (ERR_SYNTAX);
		tmp = tmp->next;
	}
	return (1);
}