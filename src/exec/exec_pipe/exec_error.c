/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaissramirez <kaissramirez@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 21:43:09 by karamire          #+#    #+#             */
/*   Updated: 2025/07/30 19:03:45 by kaissramire      ###   ########.fr       */
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

void	close_fork(int *fd1, int *fd2, t_exec *node, t_shell *main)
{
	(void)node;
	ft_safe_close(fd1, main);
	ft_safe_close(fd2, main);
	close_node(main);
}

void	error_fork(int *pipefd, int prevfd, t_exec *node, t_shell *main)
{
	(void)node;
	while (wait(NULL) > 0)
		;
	ft_putendl_fd("Fork failed", 2);
	if (prevfd > 1)
	{
		ft_safe_close(&prevfd, main);
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
	(void)node;
	while (wait(NULL) > 0)
		;
	ft_putendl_fd("Pipe failed", 2);
	ft_safe_close(&prevfd, main);
	if (main->env_tab)
		free(main->env_tab);
	free_struct(main);
	free(main);
	exit(errno);
}
