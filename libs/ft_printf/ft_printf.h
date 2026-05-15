/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otton-sousa <otton-sousa@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 13:12:23 by osousa-d          #+#    #+#             */
/*   Updated: 2026/02/08 20:35:13 by otton-sousa      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft/libft.h"
# include <stdarg.h>

int	ft_printf(const char *s, ...);
int	ft_print_char(char c);
int	ft_print_str(char *s);
int	ft_print_pointer(unsigned long ptr);
int	ft_print_nbr(long nb);
int	ft_print_unsigned(unsigned int n, int fd);
int	ft_print_hex(unsigned long n, int fd, int uppercase);

#endif