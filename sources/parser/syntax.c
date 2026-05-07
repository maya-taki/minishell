/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 22:29:37 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/05/07 20:01:45 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

int	*validate_syntax(t_token *token_list)
{
	t_token	*tmp;
	
	tmp = token_list;
	if (tmp->type == TOKEN_PIPE)
		return (ERR_SYNTAX);
	while (tmp)
	{
		if (!tmp->next)
		{
			if (tmp != TOKEN_WORD)
				return (ERR_SYNTAX);
		}
		tmp = tmp->next;
	}
}