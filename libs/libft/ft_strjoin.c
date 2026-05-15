/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osousa-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 16:17:29 by osousa-d          #+#    #+#             */
/*   Updated: 2025/07/30 16:17:33 by osousa-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str_cat;
	size_t	len_s1_s2;
	size_t	i;
	size_t	j;

	len_s1_s2 = (ft_strlen(s1) + ft_strlen(s2));
	str_cat = (char *)malloc((len_s1_s2 + 1) * sizeof(char));
	if (!str_cat)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		str_cat[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		str_cat[j + i] = s2[j];
		j++;
	}
	str_cat[i + j] = '\0';
	return (str_cat);
}
