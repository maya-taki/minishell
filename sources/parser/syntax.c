/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 22:29:37 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/05/08 19:57:15 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

int	validate_syntax(t_mini *mini)
{
	t_token	*token;
	
	token = mini;
	if (!token)
		return (1);
	if (token->type == TOKEN_PIPE)
		return (ft_printf(ERR_SYNTAX), 2);
	while (token)
	{
		if (!token->next && token->type != TOKEN_WORD)
			return (2);
		if (token->type == TOKEN_PIPE && token->next->type == TOKEN_PIPE)
			return (2);
		token = token->next;
	}
	return (1);
}