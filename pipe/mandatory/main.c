/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 18:31:58 by karamire          #+#    #+#             */
/*   Updated: 2025/04/07 11:39:34 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

pid_t	child_process(char *cmd, char **env, int prev_fd)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
		error_exit("Error : Pipe failed", EXIT_FAILURE, prev_fd);
	pid = fork();
	if (pid == -1)
	{
		close_dup_failed(pipefd[1], pipefd[0], 0);
		error_exit("Error : Fork failed", EXIT_FAILURE, prev_fd);
	}
	if (pid == 0)
	{
		close(pipefd[0]);
		if (dup2(prev_fd, STDIN_FILENO) == -1)
			close_dup_failed(pipefd[1], prev_fd, 1);
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			close_dup_failed(pipefd[1], prev_fd, 1);
		close(pipefd[1]);
		close(prev_fd);
		do_cmd(cmd, env);
	}
	close(pipefd[1]);
	close(prev_fd);
	return (pipefd[0]);
}

pid_t	last_child(char *last, int prev_fd, int outfile, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		close_dup_failed(outfile, -1, 0);
		error_exit("Error : Fork failed", EXIT_FAILURE, prev_fd);
	}
	if (pid == 0)
	{
		if (prev_fd != -1)
		{
			if (dup2(prev_fd, STDIN_FILENO) == -1)
				close_dup_failed(outfile, prev_fd, 1);
			close(prev_fd);
		}
		if (dup2(outfile, STDOUT_FILENO) == -1)
			close_dup_failed(outfile, prev_fd, 1);
		close(outfile);
		do_cmd(last, env);
	}
	return (pid);
}

void	wait_child(pid_t last)
{
	int	status;

	while (waitpid(last, &status, 0) > 0)
	{
		if (WIFEXITED(status) && WEXITSTATUS(status) == 127)
			exit(127);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
			exit(1);
	}
	while (wait(NULL) > 0)
		;
}

int	main(int ac, char **av, char **env)
{
	int		outfile;
	int		prev_fd;
	int		i;
	pid_t	last_pid;

	i = 0;
	check_args(ac);
	prev_fd = open_input(av, &i);
	if (i == 0)
		prev_fd = child_process(av[2], env, prev_fd);
	outfile = open_file(av[ac - 1], 0);
	access_out_check(av[ac - 1], prev_fd, outfile);
	last_pid = last_child(av[ac - 2], prev_fd, outfile, env);
	close_fd(prev_fd, outfile);
	wait_child(last_pid);
	return (0);
}
