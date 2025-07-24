/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 02:31:16 by ludebion          #+#    #+#             */
/*   Updated: 2025/07/24 23:30:05 by ludebion         ###   ########.fr       */
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

t_parse_error	secure_close(int *fd)
{
	if (*fd == -1)
		return (ERR_CLOSE);
	if (*fd > 1)
	{
		if (close(*fd) == -1)
		{
			print_perror("close");
			return (ERR_CLOSE);
		}
		*fd = -1;
	}
	return (ERR_NONE);
}

t_parse_error	check_std_cmd(int std, t_exec *new_cmd)
{
	if (std == STDIN_FILENO)
	{
		if (new_cmd->infile.fd == -1)
			return (ERR_PREV_OPEN);
		if (new_cmd->infile.filepath)
			free(new_cmd->infile.filepath);
		if (secure_close(&new_cmd->infile.fd) != ERR_NONE)
			return (ERR_CLOSE);
	}
	else if (std == STDOUT_FILENO)
	{
		if (new_cmd->outfile.fd == -1)
			return (ERR_PREV_OPEN);
		if (new_cmd->outfile.filepath)
			free(new_cmd->outfile.filepath);
		if (secure_close(&new_cmd->outfile.fd) != ERR_NONE)
			return (ERR_CLOSE);
	}
	return (ERR_NONE);
}

t_parse_error	create_heredoc_filepath(t_exec *new_cmd, int i)
{
	char	*hd_nbr;

	hd_nbr = ft_itoa(i);
	if (!hd_nbr)
		return (ERR_MALLOC);
	new_cmd->infile.filepath = ft_strjoin("/tmp/.ms_hd_", hd_nbr);
	free(hd_nbr);
	if (!new_cmd->infile.filepath)
		return (ERR_MALLOC);
	return (ERR_NONE);
}
