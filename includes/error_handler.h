/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osousa-d <osousa-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 17:11:17 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/04/19 22:32:44 by osousa-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_HANDLER_H
# define ERROR_HANDLER_H

# define ERR_MALLOC "Error: memory allocation failure.\n";
# define ERR_UNCLOSED_QUOTE "Error: unclosed Quote.\n";
# define ERR_SYNTAX "Error: syntax Failure.\n";
# define ERR_HEREDOC "Error: heredoc failure.\n";
# define ERR_INVALID_CHAR "Error: invalid character.\n";
# define ERR_CMD "Error: command not found.\n";
# define INVALID_REDIR "Error: invalid redirection.\n";

typedef enum e_error_type
{
	ERROR = -1,
	OK = 0,
	FAIL = 1
} t_error_type;

# endif