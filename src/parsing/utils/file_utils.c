/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 02:31:16 by ludebion          #+#    #+#             */
/*   Updated: 2025/08/26 08:06:06 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_file(const char *filepath, t_token_type file_type)
{
	if (file_type == T_REDIR_IN)
		return (open(filepath, O_RDONLY));
	else if (file_type == T_REDIR_TRUNC)
		return (open(filepath, O_CREAT | O_WRONLY | O_TRUNC, 0644));
	else if (file_type == T_REDIR_APPEND)
		return (open(filepath, O_CREAT | O_WRONLY | O_APPEND, 0644));
	return (-1);
}

t_parse_error	secure_close(int *fd, int std)
{
	if (*fd == -1)
		return (ERR_PREV_OPEN);
	if (*fd > 1)
	{
		if (close(*fd) == -1)
		{
			*fd = -1;
			print_perror("my close");
			return (ERR_CLOSE);
		}
		if (std == STDIN_FILENO)
			*fd = 0;
		else
			*fd = 1;
	}
	return (ERR_NONE);
}

t_parse_error	check_std_cmd(int std, t_exec *new_cmd)
{
	if (new_cmd->infile.fd == -1 || new_cmd->outfile.fd == -1)
	{
		if (new_cmd->infile.fd_heredoc != 0)
			if (secure_close(&new_cmd->infile.fd_heredoc,
					STDIN_FILENO) != ERR_NONE)
				return (ERR_CLOSE);
		return (ERR_PREV_OPEN);
	}
	if (std == STDIN_FILENO)
	{
		if (new_cmd->infile.fd != new_cmd->infile.fd_heredoc)
			return (secure_close(&new_cmd->infile.fd, STDIN_FILENO));
	}
	return (secure_close(&new_cmd->outfile.fd, STDOUT_FILENO));
}

void	reset_std_file(t_shell *shell, t_token *token, int std, t_exec *new_cmd)
{
	if (std == STDIN_FILENO)
		new_cmd->infile.fd = -1;
	else
		new_cmd->outfile.fd = -1;
	if (shell->error.error_type == ERR_NONE)
	{
		print_syntax_error_msg(ERR_AMBIGUOUS_REDIR, '\0', token->next->value);
		set_error_syntax(&shell->error, ERR_AMBIGUOUS_REDIR, '\0',
			token->next->value);
	}
}

char	*create_heredoc_filepath(int i)
{
	char	*filepath;
	char	*hd_nbr;

	hd_nbr = ft_itoa(i);
	if (!hd_nbr)
		return (NULL);
	filepath = ft_strjoin("/tmp/.ms_hd_", hd_nbr);
	free(hd_nbr);
	if (!filepath)
		return (NULL);
	return (filepath);
}
