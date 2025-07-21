/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 02:31:24 by ludebion          #+#    #+#             */
/*   Updated: 2025/07/19 02:31:24 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_parse_error	set_error(t_error *error, t_parse_error error_type,
		char unexpected_token)
{
	error->error_type = error_type;
	if (unexpected_token)
		error->unexpected_token = unexpected_token;
	return (error_type);
}

void	print_syntax_error_msg(t_parse_error errcode, char unexpected_token)
{
	if (errcode == ERR_MISSING_SINGLE_QUOTE)
		ft_putstr_fd("Missing single quote (').\n", STDERR_FILENO);
	else if (errcode == ERR_MISSING_DOUBLE_QUOTE)
		ft_putstr_fd("Missing double quote (\").\n", STDERR_FILENO);
	else if (errcode == ERR_SYNTAX)
	{
		ft_putstr_fd("syntax error near unexpected token ", STDERR_FILENO);
		if (!unexpected_token)
			ft_putstr_fd("`newline'", STDERR_FILENO);
		else
		{
			ft_putchar_fd('`', STDERR_FILENO);
			ft_putchar_fd(unexpected_token, STDERR_FILENO);
			ft_putchar_fd('\'', STDERR_FILENO);
		}
		ft_putchar_fd('\n', STDERR_FILENO);
	}
	else if (errcode == ERR_DOUBLE_PIPE)
		ft_putstr_fd("Double pipe.\n", STDERR_FILENO);
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
