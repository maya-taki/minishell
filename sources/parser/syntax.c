/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loena <loena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 22:29:37 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/05/09 16:28:13 by loena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

//int	validate_syntax(t_token *tokens)
//{
//	t_token	*tmp;
	
//	tmp = tokens;
//	if (!tmp)
//		return (ERR_NONE);
//	if (tmp->type == TOKEN_PIPE)
//		return (ERR_SYNTAX);
//	while (tmp)
//	{
//		if (is_redir(tmp) && (!tmp->next || tmp->next->type != TOKEN_WORD))
//			return (ERR_SYNTAX);
//		if (tmp->type == TOKEN_PIPE && tmp->next
//			&& tmp->next->type == TOKEN_PIPE)
//			return (ERR_SYNTAX);
//		tmp = tmp->next;
//	}
//	return (1);
//}
