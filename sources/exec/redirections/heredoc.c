/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 17:04:39 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/06/03 21:01:56 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

char	*remove_quotes(char *delimiter)
{
	int	delim_l;

	delim_l = strlen(delimiter);
	if (delim_l < 2)
		return (delimiter);
	if ((delimiter[0] == '\'' || delimiter[delim_l - 1] == '\'')
		|| (delimiter[0] == '"' || delimiter[delim_l - 1] == '"'))
		return (ft_substr(delimiter, 1, delim_l - 2));
	return (ft_strdup(delimiter));
}

void	write_lines(char *line, int fd)
{
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
}

void	heredoc_loop();

int	handle_heredoc(t_token *delimiter_token, t_cmd *cmd, t_shell *shell)
{
	(void)delimiter_token;
	(void)cmd;
	(void)shell;
	/* stub implementation: heredoc not fully implemented yet */
	return (1);
}
