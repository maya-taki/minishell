/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 14:38:01 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/05/06 17:24:19 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

int	open_file(int *fd_ptr, char *path, int flags)
{
	if (*fd_ptr > 2)
		close(fd_ptr);	
	fd_ptr = open(path, flags, 0644);
	if (*fd_ptr == -1)
	{
		perror(path);
		return (1);
	}
	return (0);
}

int count_cmdS(t_token *token_list)
{
	int		len;
	t_token	*tmp;
	
	len = 1;
	tmp = token_list;
	while (tmp)
	{
		if (tmp->type != TOKEN_PIPE)
			len++;
		tmp = tmp->next;
	}
	return (len);
}

int count_words(t_token *token)
{
	int	words;
	words = 0;

	
	return (words);
}