/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 13:17:39 by karamire          #+#    #+#             */
/*   Updated: 2025/04/07 11:32:09 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	check_args(int ac)
{
	if (ac != 5)
		error_exit("Error. Please provide 5 args", 2, -1);
	return (1);
}

void	error_exec(char **cmdtab, char *cmd)
{
	int	i;

	i = 0;
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(" : Command not found", 2);
	if (cmdtab[i])
	{
		while (cmdtab[i] != NULL)
		{
			free(cmdtab[i]);
			i++;
		}
	}
	free(cmdtab);
	exit(127);
}

char	*free_tab(char **tab, char **path)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			free(tab[i]);
			i++;
		}
		free(tab);
	}
	i = 0;
	if (path)
	{
		while (path[i])
		{
			free(path[i]);
			i++;
		}
		free(path);
	}
	return (NULL);
}

void	close_dup_failed(int fd1, int fd2, int i)
{
	while (wait(NULL) > 0)
		;
	if (fd1 > 0)
		close(fd1);
	if (fd2 > 0)
		close(fd2);
	if (i == 1)
		error_exit("Error. Dup2 failed.", EXIT_FAILURE, -1);
}

void	error_exit(char *str, int exitnbr, int fd)
{
	ft_putendl_fd(str, 2);
	if (fd > 0)
		close(fd);
	exit(exitnbr);
}
