/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 07:10:08 by ludebion          #+#    #+#             */
/*   Updated: 2025/08/27 08:04:38 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (unexpected_token)
			ft_putchar_fd(unexpected_token, STDERR_FILENO);
		else
			ft_putstr_fd("newline", STDERR_FILENO);
		ft_putstr_fd("'\n", STDERR_FILENO);
	}
	else if (errcode == ERR_DOUBLE_PIPE)
		ft_putstr_fd("Double pipe.\n", STDERR_FILENO);
	else if (errcode == ERR_AMBIGUOUS_REDIR)
	{
		ft_putstr_fd(ambiguous_redir, STDERR_FILENO);
		ft_putstr_fd(" : Ambiguous redirection\n", STDERR_FILENO);
	}
	else if (errcode == ERR_MALLOC)
		ft_putstr_fd("Memory allocation failed.\n", STDERR_FILENO);
	else if (errcode == ERR_PIPE)
		ft_putstr_fd("Pipe failed.\n", STDERR_FILENO);
	else if (errcode == ERR_TOKEN)
		ft_putstr_fd("An error happened while parsing token.\n", STDERR_FILENO);
}

static void	get_errcode(t_shell *shell, t_parse_error errcode)
{
	if (errcode == ERR_MALLOC || errcode == ERR_PIPE || errcode == ERR_TOKEN)
		shell->errcode = 12;
	else if (errcode >= ERR_SYNTAX && errcode <= ERR_MISSING_SINGLE_QUOTE)
		shell->errcode = 2;
	else if (errcode == ERR_TOKEN || errcode == ERR_AMBIGUOUS_REDIR
		|| errcode == ERR_PREV_OPEN || (errcode >= ERR_READ
			&& errcode <= ERR_OPEN))
		shell->errcode = 1;
	else
		shell->errcode = 0;
}

bool	check_parsing(t_shell *shell, t_parse_error errcode, bool at_end)
{
	if (errcode == ERR_NONE)
	{
		if (at_end)
			get_errcode(shell, shell->error.error_type);
		shell->error.error_type = ERR_NONE;
		shell->error.unexpected_token = '\0';
		shell->error.ambiguous_redir = NULL;
		return (true);
	}
	get_errcode(shell, errcode);
	if (errcode != ERR_SIG && !(errcode >= ERR_READ && errcode <= ERR_OPEN))
		print_syntax_error_msg(errcode, shell->error.unexpected_token,
			shell->error.ambiguous_redir);
	free_shell_error(shell);
	return (false);
}
