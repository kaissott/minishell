/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 02:31:24 by ludebion          #+#    #+#             */
/*   Updated: 2025/07/23 10:11:13 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_parse_error	set_error(t_error *error, t_parse_error error_type,
		char unexpected_token, char *ambiguous_redir)
{
	error->error_type = error_type;
	if (unexpected_token)
		error->unexpected_token = unexpected_token;
	if (ambiguous_redir)
		error->ambiguous_redir = ambiguous_redir;
	return (error_type);
}

void	print_syntax_error_msg(t_parse_error errcode, char unexpected_token,
		char *ambiguous_redir)
{
	if (errcode == ERR_MISSING_SINGLE_QUOTE)
		ft_putstr_fd("Missing single quote (').\n", STDERR_FILENO);
	else if (errcode == ERR_MISSING_DOUBLE_QUOTE)
		ft_putstr_fd("Missing double quote (\").\n", STDERR_FILENO);
	else if (errcode == ERR_SYNTAX)
	{
		ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
		if (!unexpected_token)
			ft_putstr_fd("newline'\n", STDERR_FILENO);
		else
		{
			ft_putchar_fd(unexpected_token, STDERR_FILENO);
			ft_putstr_fd("\'\n", STDERR_FILENO);
		}
	}
	else if (errcode == ERR_DOUBLE_PIPE)
		ft_putstr_fd("Double pipe.\n", STDERR_FILENO);
	else if (errcode == ERR_AMBIGUOUS_REDIR)
	{
		ft_putstr_fd(ambiguous_redir, STDERR_FILENO);
		ft_putstr_fd(" : Ambiguous redirection\n", STDERR_FILENO);
	}
	else if (errcode == ERR_MALLOC)
		ft_putstr_fd("Token creation failed (malloc error).\n", STDERR_FILENO);
}

char	*join_or_dup(char *prev, char *next)
{
	char	*new_val;

	if (prev && next)
		new_val = ft_strjoin(prev, next);
	else if (prev)
		new_val = ft_strdup(prev);
	else if (next)
		new_val = ft_strdup(next);
	else
		new_val = ft_strdup("");
	free(prev);
	return (new_val);
}

bool	is_dollar_alone(t_token_chunk *chunk, size_t i, size_t len,
		t_token_chunk *next)
{
	if (len == 1 && chunk->value[i] == '$' && chunk->type != T_DOUBLE_QUOTED
		&& next && (next->type == T_SINGLE_QUOTED
			|| next->type == T_DOUBLE_QUOTED))
	{
		while (chunk->value[i])
		{
			chunk->value[i] = chunk->value[i + 1];
			i++;
		}
		return (true);
	}
	return (false);
}
