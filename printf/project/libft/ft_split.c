/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osousa-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 16:18:29 by osousa-d          #+#    #+#             */
/*   Updated: 2025/07/30 16:18:30 by osousa-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			count++;
			while (*s && *s != c)
				s++;
		}
	}
	return (count);
}

static int	word_len(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static char	*word_dup(const char *s, int size)
{
	int		i;
	char	*str;

	i = 0;
	str = malloc((size + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (i < size)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static void	free_all(char **array, int mal_sucess)
{
	int	i;

	i = 0;
	while (i < mal_sucess)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	int		i;
	int		c_words;
	int		len;

	if (!s)
		return (NULL);
	c_words = count_words(s, c);
	array = malloc((c_words + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	i = 0;
	while (*s && i < c_words)
	{
		while (*s == c)
			s++;
		len = word_len(s, c);
		array[i] = word_dup(s, len);
		if (!array[i])
			return (free_all(array, i), NULL);
		s += len;
		i++;
	}
	array[i] = NULL;
	return (array);
}
