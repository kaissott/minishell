/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 02:30:06 by ludebion          #+#    #+#             */
/*   Updated: 2025/07/23 00:26:04 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_operator(const char *str)
{
	return (!ft_strncmp(str, ">>", 2) || !ft_strncmp(str, "<<", 2)
		|| str[0] == '|' || str[0] == '>' || str[0] == '<');
}

static t_token_type	handle_redir(char *cmd, t_error *error)
{
	size_t	i;

	i = 1;
	if ((cmd[0] == '>' && cmd[1] == '>') || (cmd[0] == '<' && cmd[1] == '<'))
		i = 2;
	while (cmd[i] && cmd[i] == ' ')
		i++;
	if (is_operator(&cmd[i]) || !cmd[i])
	{
		set_error(error, ERR_SYNTAX, cmd[i]);
		return (T_ERROR_SYNTAX);
	}
	if (cmd[0] == '>')
	{
		if (cmd[1] == '>')
			return (T_REDIR_APPEND);
		return (T_REDIR_TRUNC);
	}
	if (cmd[0] == '<')
		if (cmd[1] == '<')
			return (T_HEREDOC);
	return (T_REDIR_IN);
}

t_token_type	get_token_type(t_error *error, char *cmd)
{
	size_t	i;

	i = 1;
	if (cmd[0] == '|')
	{
		if (cmd[1] == '|')
		{
			set_error(error, ERR_DOUBLE_PIPE, '\0');
			return (T_ERROR_PIPE);
		}
		while (cmd[i] && cmd[i] == ' ')
			i++;
		if (!cmd[i] || !cmd[-1])
		{
			set_error(error, ERR_SYNTAX, '|');
			return (T_ERROR_SYNTAX);
		}
		return (T_PIPE);
	}
	else if (cmd[0] == '<' || cmd[0] == '>')
		return (handle_redir(cmd, error));
	return (T_ERROR_SYNTAX);
}

void	set_heredocs_delimiters(t_main *shell)
{
	t_token	*tmp;

	tmp = shell->token;
	while (tmp)
	{
		if (ft_strcmp(tmp->value, "<<") == 0 && tmp->next)
			tmp->next->is_delimiter = true;
		tmp = tmp->next;
	}
}
