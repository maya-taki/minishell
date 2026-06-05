/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osousa-d <osousa-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 18:37:00 by osousa-d          #+#    #+#             */
/*   Updated: 2026/06/04 23:27:09 by osousa-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"
#include <limits.h>

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
	long	digit;
	long	max_digit;

	sign = 1;
	*result = 0;
	if (str[0] == '-')
		sign = -1;
	if (str[0] == '+' || str[0] == '-')
		str++;
	max_digit = (sign > 0) ? 7 : 8;
	while (*str)
	{
		digit = *str - '0';
		if (*result > LLONG_MAX / 10)
			return (1);
		if (*result == LLONG_MAX / 10 && digit > max_digit)
			return (1);
		*result = *result * 10 + digit;
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
	{
		shell->exit_shell = 1;
		return (shell->exit_code);
	}
	if (parse_exit_arg(shell->cmd->args[1], &val))
	{
		shell->exit_code = 255;
		shell->exit_shell = 1;
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(shell->cmd->args[1], STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd((char *)error_msg(ERR_NUM_REQUIRED), STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		return (255);
	}
	if (shell->cmd->args[2])
		return (handle_error(ERR_TOO_MANY_ARGS, "exit", NULL));
	shell->exit_code = (unsigned char)val;
	shell->exit_shell = 1;
	return (shell->exit_code);
}

int	builtin_exit(t_shell *shell)
{
	int status;

	if (!shell || !shell->cmd)
		return (1);
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	status = handle_exit_args(shell);
	return (status);
}
