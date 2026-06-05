/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osousa-d <osousa-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 13:16:08 by osousa-d          #+#    #+#             */
/*   Updated: 2026/06/05 13:16:13 by osousa-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

void	reset_io(t_shell *shell)
{
	if (shell->std_in != STDIN_FILENO)
	{
		close(shell->std_in);
		shell->std_in = STDIN_FILENO;
	}
	if (shell->std_out != STDOUT_FILENO)
	{
		close(shell->std_out);
		shell->std_out = STDOUT_FILENO;
	}
}