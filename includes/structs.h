/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osousa-d <osousa-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 21:47:33 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/04/19 22:33:44 by osousa-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

#include "shell.h"
#include "enum.h"

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
} t_token;


typedef struct s_redir
{
	int				type;
	char 			*file;
	struct s_redir	*next;
}	t_redir;

// cada comando vai ser um t_cmd
// parser da maya vai entregar os dados pro meu executor no formato t_cmd
typedef struct s_cmd
{
	char			**args;
	t_builtin		builtin;
	t_redir			*redir;
	struct s_cmd	*next;

}	t_cmd;

#endif