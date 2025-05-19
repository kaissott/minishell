/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 13:19:32 by karamire          #+#    #+#             */
/*   Updated: 2025/03/31 09:23:57 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	open_input(char **av, int *i)
{
	int	infile;

	infile = open_file(av[1], 1);
	if (infile == -1)
	{
		(*i) = 1;
		infile = open("/dev/null", O_RDONLY);
		ft_putstr_fd("no such file or directory: ", 2);
		ft_putendl_fd(av[1], 2);
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
	if (num == 1)
		fd = open(file, O_RDONLY);
	if (fd == -1)
		return (-1);
	return (fd);
}
