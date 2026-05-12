/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 17:11:17 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/05/12 19:52:02 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_HANDLER_H
# define ERROR_HANDLER_H

typedef enum e_error_type
{
	ERR_NONE,
	ERR_PARSE,
	ERR_SYNTAX,
	ERR_CMD_NOT_FOUND,
	ERR_NO_FILE,
	ERR_PERMISSION,
	ERR_MALLOC,
	ERR_TOO_MANY_ARGS,
	ERR_NUM_REQUIRED,
	ERR_NOT_VALID_ID,
	ERR_HOME_NOT_SET,
	ERR_OLDPWD_NOT_SET
}	t_error_type;

#endif
