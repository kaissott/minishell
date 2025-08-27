/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 09:16:35 by ludebion          #+#    #+#             */
/*   Updated: 2025/08/27 17:22:23 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define BUFF 4096
#define PIPE_BUF_SIZE 15

bool	check_line(char *line, char *delimiter)
{
	if (!line)
	{
		ft_putstr_fd("minishell: warning : \"here-document\" ", STDIN_FILENO);
		ft_putstr_fd("delimited by end of file (instead of \"", STDIN_FILENO);
		ft_putstr_fd(delimiter, STDIN_FILENO);
		ft_putstr_fd("\")\n", STDIN_FILENO);
		return (false);
	}
	if (ft_strcmp(line, delimiter) == 0)
	{
		free(line);
		return (false);
	}
	return (true);
}

static t_parse_error	copy_pipe_to_file(int pipe_read_fd, int file_fd)
{
	char	buffer[BUFF];
	ssize_t	bytes_read;
	ssize_t	bytes_write;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(pipe_read_fd, buffer, BUFF);
		if (bytes_read == -1)
		{
			print_perror("read");
			return (ERR_READ);
		}
		bytes_write = write(file_fd, buffer, bytes_read);
		if (bytes_write != bytes_read)
		{
			print_perror("write");
			return (ERR_WRITE_HD);
		}
	}
	return (ERR_NONE);
}

static t_parse_error	do_switch(t_exec *new_cmd, int *fd_write_heredoc,
		int tmp_fd, char *filepath)
{
	t_parse_error	errcode;

	errcode = copy_pipe_to_file(new_cmd->infile.fd_heredoc, tmp_fd);
	if (errcode != ERR_NONE)
	{
		unlink(filepath);
		free(filepath);
		secure_close(&tmp_fd, STDIN_FILENO);
		return (errcode);
	}
	if (secure_close(&new_cmd->infile.fd_heredoc, STDIN_FILENO) != ERR_NONE)
		errcode = ERR_CLOSE;
	new_cmd->infile.fd_heredoc = open(filepath, O_RDONLY);
	unlink(filepath);
	free(filepath);
	*fd_write_heredoc = tmp_fd;
	return (errcode);
}

static t_parse_error	switch_pipe_to_tmpfile(t_exec *new_cmd,
		int *fd_write_heredoc)
{
	int		i;
	char	*filepath;
	int		tmp_fd;

	i = 0;
	filepath = create_heredoc_filepath(i);
	if (!filepath)
		return (ERR_MALLOC);
	tmp_fd = open(filepath, O_CREAT | O_EXCL | O_WRONLY, 0600);
	while ((tmp_fd == -1 && errno == EEXIST))
	{
		free(filepath);
		i++;
		filepath = create_heredoc_filepath(i);
		if (!filepath)
			return (ERR_MALLOC);
		tmp_fd = open(filepath, O_CREAT | O_EXCL | O_WRONLY, 0600);
	}
	if (tmp_fd == -1 && errno != EEXIST)
	{
		print_perror(filepath);
		return (ERR_OPEN);
	}
	return (do_switch(new_cmd, fd_write_heredoc, tmp_fd, filepath));
}

t_parse_error	check_heredoc(size_t *bytes_write, char *line, t_exec *new_cmd,
		int *pipe_write)
{
	t_parse_error	errcode;
	size_t			line_len;
	size_t			to_write;

	line_len = ft_strlen(line);
	to_write = line_len + 1;
	if (*bytes_write + to_write > PIPE_BUF_SIZE)
	{
		secure_close(pipe_write, STDIN_FILENO);
		errcode = switch_pipe_to_tmpfile(new_cmd, pipe_write);
		if (errcode != ERR_NONE)
		{
			free(line);
			return (errcode);
		}
	}
	*bytes_write += to_write;
	if (ft_putendl_fd(line, *pipe_write) == -1)
	{
		print_perror("write");
		return (ERR_WRITE_HD);
	}
	free(line);
	return (ERR_NONE);
}
