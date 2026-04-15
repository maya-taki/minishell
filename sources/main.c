/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osousa-d <osousa-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 18:09:20 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/04/15 12:09:14 by osousa-d         ###   ########.fr       */
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
