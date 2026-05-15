/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osousa-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 19:21:41 by osousa-d          #+#    #+#             */
/*   Updated: 2025/08/14 19:21:43 by osousa-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_hex(unsigned long n, int fd, int uppercase)
{
	int		count;
	char	*base;
	char	c;

	base = "0123456789abcdef";
	count = 0;
	if (n >= 16)
	{
		count += ft_print_hex(n / 16, fd, uppercase);
	}
	c = base[n % 16];
	if (uppercase == 1)
		c = ft_toupper(c);
	ft_putchar_fd(c, fd);
	count++;
	return (count);
}
