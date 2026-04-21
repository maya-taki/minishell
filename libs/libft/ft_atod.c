/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otton-sousa <otton-sousa@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 03:40:37 by otton-sousa       #+#    #+#             */
/*   Updated: 2026/01/26 03:42:22 by otton-sousa      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	skip_spaces(const char *str)
{
	int	i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	return (i);
}

static int	parse_sign(const char *str, int *i)
{
	int	sign;

	*i = skip_spaces(str);
	sign = 1;
	if (ft_issignal(str[*i]))
	{
		sign = ft_issignal(str[*i]);
		(*i)++;
	}
	return (sign);
}

double	ft_atod(const char *str)
{
	int		i;
	int		sign;
	double	res;
	double	div;

	res = 0;
	div = 10;
	sign = parse_sign(str, &i);
	while (ft_isdigit(str[i]))
		res = res * 10 + (str[i++] - '0');
	if (str[i] == '.')
		i++;
	while (ft_isdigit(str[i]))
	{
		res += (str[i++] - '0') / div;
		div *= 10;
	}
	return (res * sign);
}
