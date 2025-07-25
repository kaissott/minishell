/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaissramirez <kaissramirez@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 21:43:09 by karamire          #+#    #+#             */
/*   Updated: 2025/07/25 05:49:19 by kaissramire      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execve_err(t_shell *main, char **env, char *path, char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	if (env)
		free(env);
	if (path != NULL)
		free(path);
	exit_error_minishell(main, 127, NULL);
}

void	close_fork(int fd1, int fd2, t_exec *node, t_shell *main)
{
	if (fd1 != node->infile.fd && fd1 > 1)
		ft_close(main, fd1, fd2, -1);
	if (fd2 > 1)
		ft_close(main, fd2, -1, -1);
	close_node(main);
}

void	error_fork(int *pipefd, int prevfd, t_exec *node, t_shell *main)
{
	while (wait(NULL) > 0)
		;
	ft_putendl_fd("Fork failed", 2);
	if (prevfd > 1)
	{
		close_fork(prevfd, -1, node, main);
		if (main->env_tab)
			free(main->env_tab);
		free_struct(main);
		free(main);
	}
	else
	{
		if (pipefd && pipefd[0] > 0)
			ft_close(main, pipefd[0], pipefd[1], main->std_in);
		if (pipefd && pipefd[1] > 1)
			ft_close(main, pipefd[1], main->std_in, main->std_out);
		if (main->env_tab)
			free(main->env_tab);
		ft_close(main, main->std_in, main->std_out, -1);
		ft_close(main, main->std_out, -1, -1);
		free_struct(main);
		free(main);
	}
	exit(errno);
}

void	error_pipe(int prevfd, t_exec *node, t_shell *main)
{
	while (wait(NULL) > 0)
		;
	ft_putendl_fd("Pipe failed", 2);
	close_fork(prevfd, -1, node, main);
	if (main->env_tab)
		free(main->env_tab);
	free_struct(main);
	free(main);
	exit(errno);
}
