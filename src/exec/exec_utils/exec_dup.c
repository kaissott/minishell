/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_dup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 01:48:41 by karamire          #+#    #+#             */
/*   Updated: 2025/08/27 20:12:16 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	safe_dup_close(t_shell *main, int oldfd, int newfd)
{
	if (dup2(oldfd, newfd) == -1)
	{
		exit_error_two_close(main, &main->exec->infile.fd,
			&main->exec->outfile.fd);
		exit_error_minishell(main, 1, "Dup2 failed");
	}
}

int	file_dup(t_shell *main, int fd_in, int fd_out)
{
	if (fd_in == -1 || fd_out == -1)
	{
		main->errcode = 1;
		return (-1);
	}
	if (fd_in != STDIN_FILENO)
		safe_dup_close(main, fd_in, STDIN_FILENO);
	if (fd_out != STDOUT_FILENO)
		safe_dup_close(main, fd_out, STDOUT_FILENO);
	return (0);
}

void	dup_failed_err(t_shell *main, int prev_fd, int pipefd, t_exec *node)
{
	int	fd;

	fd = -1;
	if (pipefd != main->std_out)
		close_fork(&prev_fd, &pipefd, node, main);
	else
		close_fork(&prev_fd, &fd, node, main);
	ft_safe_close(&main->std_in, main);
	ft_safe_close(&main->std_out, main);
	if (main->env_tab)
		free(main->env_tab);
	free_struct(main);
	free(main);
	ft_putstr_fd("Dup failed\n", 2);
	rl_clear_history();
	exit(1);
}

int	dup_process_child(t_shell *main, t_exec *node, int prev_fd, int pipefd)
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
