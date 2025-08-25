/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 02:30:06 by ludebion          #+#    #+#             */
/*   Updated: 2025/08/22 22:33:13 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_operator(const char *str)
{
	return (!ft_strncmp(str, ">>", 2) || !ft_strncmp(str, "<<", 2)
		|| str[0] == '|' || str[0] == '>' || str[0] == '<');
}

static t_token_type	handle_redir(const char *cmd, t_error *error)
{
	size_t	i;

	i = 1;
	if ((cmd[0] == '>' && cmd[1] == '>') || (cmd[0] == '<' && cmd[1] == '<'))
		i = 2;
	while (cmd[i] && cmd[i] == ' ')
		i++;
	if (is_operator(&cmd[i]) || !cmd[i])
	{
		set_error_syntax(error, ERR_SYNTAX, cmd[i], NULL);
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

static t_token_type	handle_pipe(t_error *error, const char *cmd,
		bool begin_with_operator)
{
	size_t	i;

	i = 1;
	if (cmd[1] == '|')
	{
		set_error_syntax(error, ERR_DOUBLE_PIPE, '\0', NULL);
		return (T_ERROR_PIPE);
	}
	if (begin_with_operator)
	{
		set_error_syntax(error, ERR_SYNTAX, '|', NULL);
		return (T_ERROR_SYNTAX);
	}
	while (cmd[i] && cmd[i] == ' ' && cmd[i] == '\t')
		i++;
	if (!cmd[i] || cmd[i] == '|')
	{
		set_error_syntax(error, ERR_SYNTAX, cmd[i], NULL);
		return (T_ERROR_SYNTAX);
	}
	return (T_PIPE);
}

t_token_type	get_token_type(t_error *error, const char *cmd,
		bool begin_with_operator)
{
	if (cmd[0] == '|')
		return (handle_pipe(error, cmd, begin_with_operator));
	else if (cmd[0] == '<' || cmd[0] == '>')
		return (handle_redir(cmd, error));
	return (T_ERROR_SYNTAX);
}

void	set_heredocs_delimiters(t_shell *shell)
{
	t_token	*tmp;

	tmp = shell->token;
	while (tmp)
	{
		if (tmp->type == T_HEREDOC && tmp->next)
			tmp->next->is_delimiter = true;
		else if (tmp->type == T_REDIR_IN || tmp->type == T_REDIR_TRUNC
			|| tmp->type == T_REDIR_APPEND)
			tmp->next->is_redir = true;
		tmp = tmp->next;
	}
}
