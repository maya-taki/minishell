/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD:sources/builtin/builtin_pwd.c
/*   By: otton-sousa <otton-sousa@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 15:22:19 by osousa-d          #+#    #+#             */
/*   Updated: 2026/05/24 17:21:16 by otton-sousa      ###   ########.fr       */
=======
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 18:27:47 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/05/23 19:41:54 by mtakiyos         ###   ########.fr       */
>>>>>>> origin/maya:libftprintf/project/libft/ft_strcmp.c
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

<<<<<<< HEAD:sources/builtin/builtin_pwd.c
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		
	}
	ft_printf("%s\n", cwd);
	free(cwd);
	return (1);
=======
	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
>>>>>>> origin/maya:libftprintf/project/libft/ft_strcmp.c
}
