/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osousa-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 16:16:48 by osousa-d          #+#    #+#             */
/*   Updated: 2025/07/30 16:16:50 by osousa-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub_s;
	size_t	size_s;

	size_s = ft_strlen(s);
	if (start > size_s)
		return (ft_strdup(""));
	if (len > size_s - start)
		len = size_s - start;
	sub_s = ft_calloc(len + 1, sizeof(char));
	if (!sub_s)
		return (NULL);
	ft_memcpy(sub_s, (s + start), len);
	return (sub_s);
}
