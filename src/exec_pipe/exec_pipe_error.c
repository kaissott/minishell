/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:50:09 by karamire          #+#    #+#             */
/*   Updated: 2025/06/17 22:13:32 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_args(int ac, char **av)
{
	if (ac == 1)
		error_exit("Error. Please provide 5 args", 0, -1);
	if (ft_strcmp("here_doc", av[1]) == 0)
		if (ac < 6)
			error_exit("Error. Please provide 6 args", 0, -1);
	if (ac < 5)
		error_exit("Error. Please provide 5 args", 0, -1);
	return (1);
}

void	error_exec_b(char **cmdtab, char *cmd)
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
