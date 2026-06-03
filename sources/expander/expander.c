/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 21:44:06 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/06/03 15:05:39 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

char	*expand_word(const char *src, t_shell *shell);
static char	*append_char(char *dest, char c);
static char	*append_str(char *dest, const char *src);
static char	*get_env_value(t_env *env, const char *name);
static int	expand_args(t_cmd *cmd, t_shell *shell);
static int	expand_redirs(t_cmd *cmd, t_shell *shell);

int	expand_all(t_cmd *cmds, t_shell *shell)
{
	t_cmd	*cur;

	if (!shell)
		return (1);
	cur = cmds;
	while (cur)
	{
		if (expand_args(cur, shell) != 0)
			return (ERR_MALLOC);
		if (expand_redirs(cur, shell) != 0)
			return (ERR_MALLOC);
		cur = cur->next;
	}
	return (0);
}

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

int	expand_args(t_cmd *cmd, t_shell *shell)
{
	int	i;
	int	ret;

	if (!cmd || !cmd->args)
		return (0);
	i = 0;
	while (cmd->args[i])
	{
		ret = replace_arg(&cmd->args[i], shell);
		if (ret != 0)
			return (ret);
		i++;
	}
	return (0);
}

int	expand_redirs(t_cmd *cmd, t_shell *shell)
{
	t_redir	*redir;
	char	*new_file;

	if (!cmd)
		return (0);
	redir = cmd->redirs;
	while (redir)
	{
		if (redir->file)
		{
			new_file = expand_word(redir->file, shell);
			if (!new_file)
				return (ERR_MALLOC);
			free(redir->file);
			redir->file = new_file;
		}
		redir = redir->next;
	}
	return (0);
}

char	*expand_word(const char *src, t_shell *shell)
{
	size_t			i;
	t_quote_state	state;
	char			*result;

	if (!src || !shell)
		return (NULL);
	i = 0;
	state = QUOTE_NONE;
	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (src[i])
	{
		if (src[i] == '\'' && state == QUOTE_NONE)
		{
			state = QUOTE_SINGLE;
			i++;
			continue ;
		}
		if (src[i] == '\'' && state == QUOTE_SINGLE)
		{
			state = QUOTE_NONE;
			i++;
			continue ;
		}
		if (src[i] == '"' && state == QUOTE_NONE)
		{
			state = QUOTE_DOUBLE;
			i++;
			continue ;
		}
		if (src[i] == '"' && state == QUOTE_DOUBLE)
		{
			state = QUOTE_NONE;
			i++;
			continue ;
		}
		if (src[i] == '$' && state != QUOTE_SINGLE)
		{
			i++;
			if (src[i] == '?')
			{
				char	*code;

				code = ft_itoa(shell->exit_code);
				if (!code)
				{
					free(result);
					return (NULL);
				}
				result = append_str(result, code);
				free(code);
				if (!result)
					return (NULL);
				i++;
				continue ;
			}
			if (!src[i])
			{
				result = append_char(result, '$');
				if (!result)
					return (NULL);
				continue ;
			}
			size_t	start;
			start = i;
			while (src[i] && (ft_isalnum(src[i]) || src[i] == '_'))
				i++;
			if (start == i)
			{
				result = append_char(result, '$');
				if (!result)
					return (NULL);
				continue ;
			}
			char	*name;
			char	*value;
			char	*tmp;

			name = ft_substr(src, start, i - start);
			if (!name)
			{
				free(result);
				return (NULL);
			}
			value = get_env_value(shell->env, name);
			tmp = append_str(result, value);
			free(name);
			if (!tmp)
			{
				free(result);
				return (NULL);
			}
			result = tmp;
			continue ;
		}
		result = append_char(result, src[i]);
		if (!result)
			return (NULL);
		i++;
	}
	return (result);
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

char	*append_char(char *dest, char c)
{
	char	*new_dest;
	int		dest_l;

	if (!dest)
	{
		new_dest = malloc(2);
		if (!new_dest)
			return (NULL);
		new_dest[0] = c;
		new_dest[1] = '\0';
		return (new_dest);
	}
	dest_l = ft_strlen(dest);
	new_dest = malloc(dest_l + 2);
	if (!new_dest)
		return (NULL);
	memcpy(new_dest, dest, dest_l);
	new_dest[dest_l] = c;
	new_dest[dest_l + 1] = '\0';
	free(dest);
	return (new_dest);
}

char	*append_str(char *dest, const char *src)
{
	size_t		dest_l;
	size_t		src_l;
	char		*new_dest;

	if (!src)
		return (dest);
	if (!dest)
	{
		new_dest = ft_strdup(src);
		return (new_dest);
	}
	dest_l = ft_strlen(dest);
	src_l = ft_strlen(src);
	new_dest = malloc(dest_l + src_l + 1);
	if (!new_dest)
		return (NULL);
	ft_memcpy(new_dest, dest, dest_l);
	ft_memcpy(new_dest + dest_l, src, src_l);
	new_dest[dest_l + src_l] = '\0';
	free(dest);
	return (new_dest);
}

int	is_single_quoted(char *arg)
{
	t_quote_state	state;
	int			i;

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
