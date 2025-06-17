/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_dup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 01:48:41 by karamire          #+#    #+#             */
/*   Updated: 2025/06/17 20:20:10 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	safe_dup_close(t_main *main, int oldfd, int newfd)
{
	if (dup2(oldfd, newfd) == -1)
	{
		exit_error_two_close(main, &main->exec->infile.fd, &main->exec->outfile.fd);
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
int	dup_process_child(t_main *main, t_exec *node, int prev_fd, int pipefd)
{
	if (node->infile.fd > 1)
	{
		if (dup2(node->infile.fd, STDIN_FILENO) == -1)
		{
			exit_error_one_close(main, &node->infile.fd);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		if (dup2(prev_fd, STDIN_FILENO) == -1)
		{
			exit_error_one_close(main, &prev_fd);
			exit(EXIT_FAILURE);
		}
	}
	if (node->outfile.fd > 1)
	{
		if (dup2(node->outfile.fd, STDOUT_FILENO) == -1)
		{
			exit_error_one_close(main, &node->outfile.fd);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		if (dup2(pipefd, STDOUT_FILENO) == -1)
		{
			exit_error_one_close(main, &pipefd);
			exit(EXIT_FAILURE);
		}
	}
	return (0);
}



