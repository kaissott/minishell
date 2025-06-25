/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_dup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luca <luca@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 01:48:41 by karamire          #+#    #+#             */
/*   Updated: 2025/06/23 15:35:15 by luca             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	safe_dup_close(t_main *main, int oldfd, int newfd)
{
	if (dup2(oldfd, newfd) == -1)
	{
		exit_error_two_close(main, main->exec->infile.fd,
			main->exec->outfile.fd);
		exit_error_minishell(main, errno, "Dup2 failed");
	}
}

void	file_dup(t_main *main, int fd_in, int fd_out)
{
	if (fd_in != STDIN_FILENO)
		safe_dup_close(main, fd_in, STDIN_FILENO);
	if (fd_out != STDOUT_FILENO)
		safe_dup_close(main, fd_out, STDOUT_FILENO);
}

void	close_main_fds(t_main *main)
{
	free_struct(main);
}

void	dup_failed_err(t_main *main, int prev_fd, int pipefd, t_exec *node)
{
	close_fork(prev_fd, pipefd, node, main);
	if (main->envtab)
		free(main->envtab);
	free_struct(main);
	free(main);
	ft_putstr_fd("Dup failed\n", 2);
	exit(errno);
}
int	dup_process_child(t_main *main, t_exec *node, int prev_fd, int pipefd)
{
	if (node->infile.fd > 1)
	{
		if (dup2(node->infile.fd, STDIN_FILENO) == -1)
			dup_failed_err(main, prev_fd, pipefd, node);
	}
	else if (dup2(prev_fd, STDIN_FILENO) == -1)
		dup_failed_err(main, prev_fd, pipefd, node);
	if (node->outfile.fd > 1)
	{
		if (dup2(node->outfile.fd, STDOUT_FILENO) == -1)
			dup_failed_err(main, prev_fd, pipefd, node);
	}
	else if (dup2(pipefd, STDOUT_FILENO) == -1)
		dup_failed_err(main, prev_fd, pipefd, node);
	return (0);
}
