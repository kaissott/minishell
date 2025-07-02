/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:50:09 by karamire          #+#    #+#             */
/*   Updated: 2025/07/02 19:01:11 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"



char	*free_tab_pipe(char **tab, char **path)
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

void	close_fork_failed(int fd1, int fd2, int fd3, t_main *main)
{
	while (wait(NULL) > 0)
		;
	close(fd3);
	exit_error_two_close(main, fd1, fd2);
	exit_error_minishell(main, errno, "Dup failed");
}

void	error_exit(char *str, int exitnbr, int fd)
{
	if (fd > 0)
		close(fd);
	ft_putendl_fd(str, 2);
	exit(exitnbr);
}
