// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   heredoc.c                                          :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2026/05/28 17:04:39 by mtakiyos          #+#    #+#             */
// /*   Updated: 2026/05/28 20:16:03 by mtakiyos         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../../includes/shell.h"

// int		is_quoted(char *delimiter);

// void	remove_quotes(char *delimiter)
// {
// 	int	delim_l;
// 	int	i;

// 	delim_l = strlen(delimiter);
// 	if (delim_l < 2)
// 		return ;
// 	if ((delimiter[0] == '\'' || delimiter[delim_l - 1] == '\'')
// 		|| (delimiter[0] == '"' || delimiter[delim_l - 1] == '"'))
// 	{
// 		i = 0;
// 		while (i < delim_l - 2)
// 		{
// 			delimiter[i] = delimiter[i + 1];
// 			i++;
// 		}
// 		delimiter[i] = '\0';
// 	}
// }
