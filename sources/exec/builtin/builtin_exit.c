/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osousa-d <osousa-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 18:37:00 by osousa-d          #+#    #+#             */
/*   Updated: 2026/06/05 03:44:44 by osousa-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"
#include <limits.h>

static int	is_valid_number_format(const char *str);
static int	safe_atol(const char *str, long *result);
static int	parse_exit_arg(const char *arg, long *val);
static int	handle_exit_args(t_shell *shell);	


int	builtin_exit(t_shell *shell)
{
	int status;

	if (!shell || !shell->cmd)
		return (1);
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	status = handle_exit_args(shell);
	return (status);
}

static int	is_valid_number_format(const char *str)
{
	if (!str || !str[0])
		return (0);
	if (str[0] == '+' || str[0] == '-')
		str++;
	if (!str[0] || !ft_isdigit(str[0]))
		return (0);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

static int	safe_atol(const char *str, long *result)
{
	int		sign;
	long	max_digit;
	long	digit;

	sign = get_sign_and_advance(&str);
	*result = 0;
	max_digit = get_max_digit(sign);
	while (*str)
	{
		digit = *str - '0';
		if (check_overflow_and_add(result, digit, max_digit))
			return (1);
		str++;
	}
	*result *= sign;
	return (0);
}

static int	parse_exit_arg(const char *arg, long *val)
{
	if (!is_valid_number_format(arg) || safe_atol(arg, val))
		return (1);
	return (0);
}
static int	handle_exit_args(t_shell *shell)
{
	long	val;

	if (!shell->cmd || !shell->cmd->args || !shell->cmd->args[1])
		return (handle_no_arg_exit(shell));
	if (parse_exit_arg(shell->cmd->args[1], &val))
		return (handle_invalid_arg_exit(shell));
	if (shell->cmd->args[2])
		return (handle_error(ERR_TOO_MANY_ARGS, "exit", NULL));
	shell->exit_code = (unsigned char)val;
	shell->exit_shell = 1;
	return (shell->exit_code);
}


