/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 17:35:09 by karamire          #+#    #+#             */
/*   Updated: 2025/03/31 09:09:03 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

int	heredoc(char *infile, char *limiter)
{
	int		fd;
	char	*line;

	fd = open(infile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (-1);
	while (1)
	{
		write(1, "pipe here_doc> ", 15);
		line = get_next_line(0, 0);
		if (!line)
			break ;
		if (ft_strcmp(line, limiter) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd);
		free(line);
	}
	get_next_line(0, 1);
	close(fd);
	return (fd = open(infile, O_RDONLY));
}

int	open_input(char **av, int *i, int *if_hd)
{
	int	infile;

	if (ft_strcmp("here_doc", av[1]) == 0)
	{
		infile = heredoc("here_doc", av[2]);
		(*if_hd) = 2;
		(*i) = 1;
	}
	else
	{
		infile = open_file(av[1], 1);
		if (infile == -1)
		{
			(*i) = 1;
			infile = open("/dev/null", O_RDONLY);
			ft_putstr_fd("no such file or directory: ", 2);
			ft_putendl_fd(av[1], 2);
		}
	}
	if (infile == -1)
		error_exit("Error at open infile", EXIT_FAILURE, -1);
	return (infile);
}

int	open_file(char *file, int num)
{
	int	fd;

	if (num == 0)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (num == 2)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (num == 1)
		fd = open(file, O_RDONLY);
	if (fd == -1)
		return (-1);
	return (fd);
}
