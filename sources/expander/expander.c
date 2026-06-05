/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 21:44:06 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/06/04 20:50:55 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"


int	expand_all(t_cmd *cmds, t_shell *shell)
{
	t_cmd	*cur;

	if (!shell || !cmds)
		return (0);
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

static char	*expand_dollar(const char *src, size_t *i, t_shell *shell, char *result)
{
	size_t start = *i;
	char *code, *tmp;
	if (src[*i] == '?')
	{
		code = ft_itoa(shell->exit_code);
		if (!code)
			return (free(result), NULL);
		result = append_str(result, code);
		free(code);
		return ((*i)++, result);
	}
	while (src[*i] && (ft_isalnum(src[*i]) || src[*i] == '_'))
		(*i)++;
	if (*i == start)
		return (append_char(result, '$'));
	if (!(tmp = ft_substr(src, start, *i - start)))
		return (free(result), NULL);
	result = append_str(result, get_env_value(shell->env, tmp));
	free(tmp);
	return (result);
}

char	*expand_word(const char *src, t_shell *shell)
{
	size_t i = 0;
	t_quote_state state = QUOTE_NONE;
	char *result;
	if (!src || !shell || !(result = ft_strdup("")))
		return (NULL);
	while (src[i])
	{
		update_quote_state_iterate(src, &state, &i);
		if (src[i] == '$' && state != QUOTE_SINGLE)
		{
			i++;
			result = expand_dollar(src, &i, shell, result);
		}
		else
			result = append_char(result, src[i++]);
		if (!result)
			return (NULL);
	}
	return (result);
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
