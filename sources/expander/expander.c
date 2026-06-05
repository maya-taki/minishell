/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 21:44:06 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/06/05 06:06:35 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

void	expand_all(t_cmd *cmds, t_shell *shell)
{
	t_cmd	*cur;

	if (!shell || !cmds)
		return ;
	cur = cmds;
	while (cur)
	{
		if (expand_args(cur, shell) != 0)
			return ;
		if (expand_redirs(cur, shell) != 0)
			return ;
		cur = cur->next;
	}
}

int	expand_args(t_cmd *cmd, t_shell *shell)
{
	int	i;
	int	ret;

	if (!cmd || !cmd->args)
		return (0);
	i = 0;
	cmd->expanded_args = cmd->args;
	while (cmd->expanded_args[i])
	{
		ret = replace_arg(&cmd->expanded_args[i], shell);
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

static char	*expand_dol(const char *src, size_t *i, t_shell *shell, char *res)
{
	size_t	start;
	char	*tmp;
	char	*code;

	start = *i;
	if (src[*i] == '?')
	{
		code = ft_itoa(shell->exit_code);
		if (!code)
			return (free(res), NULL);
		res = append_str(res, code);
		free(code);
		return ((*i)++, res);
	}
	while (src[*i] && (ft_isalnum(src[*i]) || src[*i] == '_'))
		(*i)++;
	if (*i == start)
		return (append_char(res, '$'));
	tmp = ft_substr(src, start, *i - start);
	if (!tmp)
		return (free(res), NULL);
	res = append_str(res, get_env_value(shell->env, tmp));
	free(tmp);
	return (res);
}

char	*expand_word(const char *src, t_shell *shell)
{
	size_t			i;
	t_quote_state	state;
	char			*result;

	state = QUOTE_NONE;
	i = 0;
	result = ft_strdup("");
	if (!src || !shell || !result)
		return (NULL);
	while (src[i])
	{
		update_quote_state_i(src, &state, &i);
		if (src[i] == '$' && state != QUOTE_SINGLE)
		{
			i++;
			result = expand_dol(src, &i, shell, result);
		}
		else
			result = append_char(result, src[i++]);
		if (!result)
			return (NULL);
	}
	return (result);
}
