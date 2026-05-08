/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osousa-d <osousa-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 20:32:26 by osousa-d          #+#    #+#             */
/*   Updated: 2026/05/08 19:18:52 by osousa-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	parser_env_line(char *envp, t_env *node)
{
	char *equal;

	equal = ft_strchr(envp, '=');
	if (equal == NULL)
		return ;
	node->key = ft_substr(envp, 0, equal - envp);
	node->value = ft_strdup(equal + 1);
}
