/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 18:09:20 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/04/11 21:01:22 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	main(int ac, char **av)
{
	char	*word = "|";
	t_token	*token;
	t_token	*tmp;
	
	token = lexer(word);
	tmp = token;
	(void)ac;
	(void)av;
	while (tmp->value)
	{		
		printf("%d %s test\n", tmp->type, tmp->value);
		tmp = tmp->next;
	}
	return (OK);
}