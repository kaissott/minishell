/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 09:16:35 by ludebion          #+#    #+#             */
/*   Updated: 2025/08/26 09:17:46 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define BUFF 4096
#define PIPE_BUF_SIZE 15

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
			print_perror("read from pipe");
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

static t_parse_error	create_heredoc(t_exec *new_cmd, int *fd_write_heredoc)
{
	int				i;
	char			*filepath;
	int				tmp_fd;
	t_parse_error	errcode;

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
	return (ERR_NONE);
}

static bool	check_line(char *line, char *delimiter)
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

static t_parse_error	check_heredoc(size_t *bytes_write, char *line,
		t_exec *new_cmd, int *pipe_write)
{
	t_parse_error	errcode;
	size_t			line_len;
	size_t			to_write;

	line_len = ft_strlen(line);
	to_write = line_len + 1;
	if (*bytes_write + to_write > PIPE_BUF_SIZE)
	{
		secure_close(pipe_write, STDIN_FILENO);
		errcode = create_heredoc(new_cmd, pipe_write);
		if (errcode != ERR_NONE)
			return (errcode);
	}
	*bytes_write += to_write;
	if (ft_putendl_fd(line, *pipe_write) == -1)
	{
		print_perror("write");
		return (ERR_WRITE_HD);
	}
	return (ERR_NONE);
}

static void	write_in_heredoc(t_parse_error *err, t_exec *new_cmd,
		int *pipe_write, char *delimiter)
{
	char	*rl;
	size_t	bytes_write;

	bytes_write = 0;
	while (1)
	{
		rl = NULL;
		if (isatty(STDIN_FILENO))
			rl = readline("heredoc> ");
		if (g_sig_mode == SIGINT)
		{
			free(rl);
			*err = ERR_SIG;
			return ;
		}
		if (!check_line(rl, delimiter))
			break ;
		*err = check_heredoc(&bytes_write, rl, new_cmd, pipe_write);
		if (*err != ERR_NONE)
			return ;
	}
}

t_parse_error	handle_in_heredoc(t_exec *new_cmd, int *pipe_write,
		char *delimiter)
{
	t_parse_error	errcode;

	rl_event_hook = rl_hook;
	errcode = ERR_NONE;
	init_sigaction_hd();
	write_in_heredoc(&errcode, new_cmd, pipe_write, delimiter);
	rl_event_hook = NULL;
	init_sigaction();
	if (errcode == ERR_SIG)
	{
		if (secure_close(&new_cmd->infile.fd_heredoc, STDIN_FILENO) != ERR_NONE)
			errcode = ERR_CLOSE;
		free_exec(new_cmd);
	}
	if (secure_close(pipe_write, STDIN_FILENO) != ERR_NONE)
		return (ERR_CLOSE);
	return (errcode);
}
