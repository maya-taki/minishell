/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osousa-d <osousa-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 18:09:20 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/04/19 21:28:30 by osousa-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// adaptando a main para os testes do executor
int main(void)
{
	t_cmd *cmd;

	cmd = create_test_cmd();
	execute(cmd);
	return (0);
}
