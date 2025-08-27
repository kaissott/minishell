/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 07:10:08 by ludebion          #+#    #+#             */
/*   Updated: 2025/08/27 02:06:00 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	rl_hook(void)
{
	return (0);
}

bool	is_ascii_printable(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
	{
		if (!(((unsigned char)s[i] >= 32 && (unsigned char)s[i] <= 126)
				|| s[i] == '\n' || s[i] == '\t'))
			return (false);
		i++;
	}
	return (true);
}

void	print_perror(char *error)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	perror(error);
}

t_parse_error	set_error_syntax(t_error *error, t_parse_error error_type,
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
	ft_putstr_fd("minishell: ", STDERR_FILENO);
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
	else if (errcode == ERR_MALLOC || errcode == ERR_PIPE)
		ft_putstr_fd("Memory allocation failed.\n", STDERR_FILENO);
}
