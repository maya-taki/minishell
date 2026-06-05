/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 17:04:39 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/06/05 14:17:10 by mtakiyos         ###   ########.fr       */
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

void	write_line(char *line, int fd)
{
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
}

void	heredoc_loop(char *delimiter, int expand, t_shell *shell, int fd)
{
	char	*line;
	char	*expanded;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (!ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1))
		{
			free(line);
			break ;
		}
		if (expand)
		{
			expanded = expand_word(line, shell);
			write_line(expanded, fd);
			free(expanded);
		}
		else
			write_line(line, fd);
		free(line);
	}
}

int	handle_heredoc(char *delimiter, t_shell *shell)
{
	int		fd[2];
	int		expand;
	char	*clean_delimiter;

	if (pipe(fd) == -1)
		return (perror("pipe"), 1);
	expand = !is_single_quoted(delimiter);
	clean_delimiter = remove_quotes(delimiter);
	heredoc_loop(delimiter, expand, shell, fd[1]);
	close(fd[1]);
	shell->std_in = fd[0];
	free(clean_delimiter);
	return (0);
}
