/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 02:31:19 by ludebion          #+#    #+#             */
/*   Updated: 2025/07/23 10:04:02 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	free_shell(t_shell *shell)
{
	if (shell->token)
		free_token_lst(&shell->token);
	if (shell->exec)
		free_exec_lst(&shell->exec);
	shell->error.error_type = ERR_NONE;
	shell->error.unexpected_token = '\0';
}

static void	get_errcode(t_shell *shell, t_parse_error errcode)
{
	if (errcode == ERR_MALLOC)
		shell->errcode = 12;
	else if (errcode >= ERR_DOUBLE_PIPE && errcode <= ERR_MISSING_SINGLE_QUOTE)
		shell->errcode = 2;
	else if (errcode == ERR_TOKEN)
		shell->errcode = 1;
	else if (errcode >= ERR_CLOSE && errcode <= ERR_OPEN)
		shell->errcode = 1;
	else
		shell->errcode = 0;
}

bool	check_parsing(t_shell *shell, t_parse_error errcode, bool at_end)
{
	if (errcode == ERR_NONE)
	{
		if (at_end)
			get_errcode(shell, errcode);
		return (true);
	}
	get_errcode(shell, errcode);
	if (errcode != ERR_SIG)
		print_syntax_error_msg(errcode, shell->error.unexpected_token,
			shell->error.ambiguous_redir);
	free_shell(shell);
	if (errcode == ERR_MALLOC)
	{
		free(shell);
		exit(EXIT_FAILURE);
	}
	else
		return (false);
}
