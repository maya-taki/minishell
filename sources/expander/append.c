/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 05:47:26 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/06/05 05:48:01 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

char	*append_char(char *dest, char c)
{
	char	*new_dest;
	int		dest_l;

	if (!dest)
	{
		new_dest = malloc(2);
		if (!new_dest)
			return (NULL);
		new_dest[0] = c;
		new_dest[1] = '\0';
		return (new_dest);
	}
	dest_l = ft_strlen(dest);
	new_dest = malloc(dest_l + 2);
	if (!new_dest)
		return (NULL);
	memcpy(new_dest, dest, dest_l);
	new_dest[dest_l] = c;
	new_dest[dest_l + 1] = '\0';
	free(dest);
	return (new_dest);
}

char	*append_str(char *dest, const char *src)
{
	size_t		dest_l;
	size_t		src_l;
	char		*new_dest;

	if (!src)
		return (dest);
	if (!dest)
	{
		new_dest = ft_strdup(src);
		return (new_dest);
	}
	dest_l = ft_strlen(dest);
	src_l = ft_strlen(src);
	new_dest = malloc(dest_l + src_l + 1);
	if (!new_dest)
		return (NULL);
	ft_memcpy(new_dest, dest, dest_l);
	ft_memcpy(new_dest + dest_l, src, src_l);
	new_dest[dest_l + src_l] = '\0';
	free(dest);
	return (new_dest);
}
