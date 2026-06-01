/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 21:44:06 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/06/01 14:29:15 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

int	expand_all(t_cmd *cmds, , t_shell *shell)
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

	if (!cmd || !!cmd->args)
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
	t_redir *redir;
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

char *append_char(char *dest, char c)
{
	int	len;
	char *new_str;

	if (!dest)
	{
		new_str = malloc(2);
		dest[0] = c;
		dest[1] = '\0';
		return (new_str);
	}
	len = ft_strlen(dest);
	new_str = malloc(len + 2);
	if (!new_str)
		return (NULL);
	ft_memcpy(new_str, dest, len);
	new_str[len] = c;
	new_str[len + 1] = '\0';
	free(dest);
	return (new_str);
}
char	*append_str();

int	is_single_quoted(char *arg)
{
	t_quote_state	state;
	int				i;

	i = 0;
	if (!arg)
		return (1);
	state = QUOTE_NONE;
	if  (arg[0] == "\'")
	{
		while (arg[i])
		{
			update_quote_state(arg[i], state);
			i++;
		}
		if (state == QUOTE_NONE && (arg[i - 1] == "\'"))
			return (0);
	}
	else
		return (1);
	return (0);
}

