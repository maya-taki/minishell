/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osousa-d <osousa-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 00:00:00 by osousa-d          #+#    #+#             */
/*   Updated: 2026/06/05 04:06:52 by osousa-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"
#include <limits.h>

int	get_sign_and_advance(const char **str)
{
	int	sign;

	sign = 1;
	if (**str == '-')
		sign = -1;
	if (**str == '+' || **str == '-')
		(*str)++;
	return (sign);
}

long	get_max_digit(int sign)
{
	if (sign > 0)
		return (7);
	return (8);
}

int	check_overflow_and_add(long *result, long digit, long max_digit)
{
	if (*result > LLONG_MAX / 10)
		return (1);
	if (*result == LLONG_MAX / 10 && digit > max_digit)
		return (1);
	*result = *result * 10 + digit;
	return (0);
}

void	print_exit_error(const char *arg)
{
	ft_putstr_fd((char *)"minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd((char *)arg, STDERR_FILENO);
	ft_putstr_fd((char *)": ", STDERR_FILENO);
	ft_putstr_fd((char *)error_msg(ERR_NUM_REQUIRED), STDERR_FILENO);
	ft_putstr_fd((char *)"\n", STDERR_FILENO);
}

int	handle_no_arg_exit(t_shell *shell)
{
	shell->exit_shell = 1;
	return (shell->exit_code);
}

int	handle_invalid_arg_exit(t_shell *shell)
{
	shell->exit_code = 255;
	shell->exit_shell = 1;
	print_exit_error(shell->cmd->args[1]);
	return (255);
}
