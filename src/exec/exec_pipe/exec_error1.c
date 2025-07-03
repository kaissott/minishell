/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 21:43:09 by karamire          #+#    #+#             */
/*   Updated: 2025/07/03 21:51:00 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	execve_err(t_main *main, char **env, char *path, char *cmd)
{
	ft_putstr_fd("bash: ", 2);
	perror(cmd);
	if (env)
		free(env);
	if (path != NULL)
		free(path);
	exit_error_minishell(main, 127, NULL);
}

void	close_fork(int fd1, int fd2, t_exec *node, t_main *main)
{
	int	i;

	i = 0;
	if (fd1 != node->infile.fd && fd1 > 1 && close(fd1) == -1)
	{
		i = 1;
		dprintf(2, "ici %s\n", node->cmd[0]);
	}
	if (fd2 > 1 && close(fd2) == -1)
	{
		i = 1;
		dprintf(2, "la");
	}
	if (i == 0)
	{
		close(main->std_in);
		close(main->std_out);
		close_node(main);
	}
	else
	{
		exit_error_minishell(main, errno, "close failed");
	}
}

void	error_fork(int *pipefd, int prevfd, t_exec *node, t_main *main)
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
		if (pipefd[0] > 1 && close(pipefd[0]) == -1)
			perror("close");
		if (main->env_tab)
			free(main->env_tab);
		;
		close_fork(prevfd, pipefd[1], node, main);
		free_struct(main);
		free(main);
	}
	exit(errno);
}

void	error_pipe(int prevfd, t_exec *node, t_main *main)
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
