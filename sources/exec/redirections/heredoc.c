/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 17:04:39 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/06/09 22:28:34 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

static char	*remove_quotes(char *delimiter)
{
	int	delim_l;

	delim_l = strlen(delimiter);
	if (delim_l < 2)
		return (ft_strdup(delimiter));
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

static int	heredoc_error_handler(char *delimiter, char *line)
{
	if (!line)
	{
		ft_putstr_fd("minishell: warning: here-document \
				delimited by end-of-file (wanted `", 2);
		ft_putstr_fd(delimiter, 2);
		ft_putendl_fd("')", 2);
		return (1);
	}
	if (!ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1))
	{
		free(line);
		return (1);
	}
	return (0);
}

static int	heredoc_loop(char *delimiter, int expand, t_shell *shell, int fd)
{
	char	*line;
	char	*expanded;

	setup_heredoc_signals();
	while (1)
	{
		if (g_signal == 130)
			return (130);
		line = readline("> ");
		if (g_signal == 130)
		{
			free(line);
			return (130);
		}
		if (heredoc_error_handler(delimiter, line) != 0)
			break ;
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
	return (0);
}

int	handle_heredoc(char *delimiter, t_shell *shell)
{
	int		fd[2];
	int		expand;
	int		status;
	char	*clean_delimiter;

	if (pipe(fd) == -1)
		return (perror("pipe"), 1);
	expand = !is_single_quoted(delimiter);
	clean_delimiter = remove_quotes(delimiter);
	status = heredoc_loop(clean_delimiter, expand, shell, fd[1]);
	free(clean_delimiter);
	close(fd[1]);
	if (status != 0)
	{
		close(fd[0]);
		shell->exit_code = status;
		if (status == 130)
			g_signal = 0;
		return (1);
	}
	shell->std_in = fd[0];
	return (0);
}
