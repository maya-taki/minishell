/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osousa-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 19:09:33 by osousa-d          #+#    #+#             */
/*   Updated: 2025/07/21 19:09:38 by osousa-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*src_2;
	unsigned char	*dest_2;

	if (!dest && !src)
		return (NULL);
	dest_2 = (unsigned char *)dest;
	src_2 = (unsigned char *)src;
	while (n--)
		*dest_2++ = *src_2++;
	return (dest);
}
