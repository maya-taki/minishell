/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osousa-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 12:28:26 by osousa-d          #+#    #+#             */
/*   Updated: 2025/08/14 12:28:30 by osousa-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	read_spec(va_list args, char specifier)
{
	int	count;

	count = 0;
	if (specifier == 'c')
		count += ft_print_char(va_arg(args, int));
	else if (specifier == 's')
		count += ft_print_str(va_arg(args, char *));
	else if (specifier == 'p')
		count += ft_print_pointer(va_arg(args, unsigned long));
	else if (specifier == 'd' || specifier == 'i')
		count += ft_print_nbr(va_arg(args, int));
	else if (specifier == 'u')
		count += ft_print_unsigned(va_arg(args, unsigned int), 1);
	else if (specifier == 'x')
		count += ft_print_hex(va_arg(args, unsigned int), 1, 0);
	else if (specifier == 'X')
		count += ft_print_hex(va_arg(args, unsigned int), 1, 1);
	else if (specifier == '%')
		count += ft_print_char('%');
	return (count);
}

int	ft_printf(const char *s, ...)
{
	int		i;
	int		count;
	va_list	args;

	va_start(args, s);
	count = 0;
	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] == '%' && s[i + 1])
		{
			count += read_spec(args, s[i + 1]);
			i += 2;
		}
		else
		{
			count += ft_print_char(s[i]);
			i++;
		}
	}
	va_end(args);
	return (count);
}
