/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 21:43:09 by karamire          #+#    #+#             */
/*   Updated: 2025/07/24 08:19:07 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execve_err(t_shell *main, char **env, char *path, char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	perror(cmd);
	if (env)
		free(env);
	if (path != NULL)
		free(path);
	exit_error_minishell(main, 127, NULL);
}

void	close_fork(int fd1, int fd2, t_exec *node, t_shell *main)
{
	if (fd1 != node->infile.fd && fd1 > 1)
		close(fd1);
	if (fd2 > 1)
		close(fd2);
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
			close(pipefd[0]);
		if (pipefd && pipefd[1] > 1)
			close(pipefd[1]);
		if (main->env_tab)
			free(main->env_tab);
		close(main->std_in);
		close(main->std_out);
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
