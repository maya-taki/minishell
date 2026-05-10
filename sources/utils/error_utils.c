/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loena <loena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 20:03:22 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/05/09 16:14:36 by loena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

const char	*error_msg(t_error_type error)
{
	const char	*message[] = {
		NULL,
		"syntax error near unexpected token: ",
		"command not found",
		"No such file or directory",
		"Permission denied",
		"memory allocation failed",
		"too many arguments",
		"numeric argument required",
		"not a valid identifier",
		"HOME not set",
		"OLDPWD not set"
	};
	if (error <= ERR_NONE || error > ERR_OLDPWD_NOT_SET)
		return (NULL);
	return (message[error]);
}

int	handle_error(t_error_type error, char *cmd, char *context)
{
	const char *msg;

	msg = error_msg(error);
	if (!msg)
		ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (cmd)
	{
			ft_putstr_fd(cmd, STDERR_FILENO);
			ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (context && error != ERR_SYNTAX)
	{
		ft_putstr_fd(context, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putstr_fd((char *)msg, STDERR_FILENO);
	if (context && error == ERR_SYNTAX)
		ft_putstr_fd(context, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (1);
}

