/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osousa-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:27:10 by osousa-d          #+#    #+#             */
/*   Updated: 2025/07/25 16:27:12 by osousa-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int		i;
	char	*l;

	l = NULL;
	i = 0;
	while (str[i])
	{
		if (str[i] == (unsigned char)c)
			l = (char *)&str[i];
		i++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)&str[i]);
	return (l);
}
