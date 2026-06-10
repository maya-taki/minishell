/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 17:27:46 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/06/05 05:47:43 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

int	replace_arg(char **arg_ptr, t_shell *shell)
{
	char	*old;
	char	*expanded;

	old = *arg_ptr;
	expanded = expand_word(old, shell);
	if (!expanded)
		return (ERR_MALLOC);
	free(old);
	*arg_ptr = expanded;
	return (0);
}

void	update_quote_state_i(const char *src, t_quote_state *state, size_t *i)
{
	if (src[*i] == '\'' && *state == QUOTE_NONE)
	{
		(*i)++;
		*state = QUOTE_SINGLE;
	}
	else if (src[*i] == '\'' && *state == QUOTE_SINGLE)
	{
		(*i)++;
		*state = QUOTE_NONE;
	}
	else if (src[*i] == '"' && *state == QUOTE_NONE)
	{
		(*i)++;
		*state = QUOTE_DOUBLE;
	}
	else if (src[*i] == '"' && *state == QUOTE_DOUBLE)
	{
		(*i)++;
		*state = QUOTE_NONE;
	}
}

char	*get_env_value(t_env *env, const char *name)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, name) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

int	is_single_quoted(char *arg)
{
	t_quote_state	state;
	int				i;

	if (!arg)
		return (1);
	state = QUOTE_NONE;
	i = 0;
	if (arg[0] == '\'')
	{
		while (arg[i])
		{
			update_quote_state(arg[i], &state);
			i++;
		}
		if (state == QUOTE_NONE && arg[i - 1] == '\'')
			return (0);
	}
	return (1);
}
