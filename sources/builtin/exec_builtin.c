/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osousa-d <osousa-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 19:33:55 by osousa-d          #+#    #+#             */
/*   Updated: 2026/04/29 19:34:12 by osousa-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

t_builtin get_builtin(char *arg)
{
	if (ft_strcmp(arg, "echo") == 0)
		return (ECHO);
	if (ft_strcmp(arg, "cd") == 0)
		return (CD);
	if (ft_strcmp(arg, "pwd") == 0)
		return (PWD);
	else
		return (NONE);
}
