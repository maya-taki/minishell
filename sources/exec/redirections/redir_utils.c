/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 18:03:46 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/06/03 19:22:40 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

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
