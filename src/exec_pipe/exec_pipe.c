/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:45:05 by karamire          #+#    #+#             */
/*   Updated: 2025/06/17 18:34:12 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"

void safe_close(int *fd)
{
	if (*fd > 2) {
		close(*fd);
		*fd = -1;
	}
}

void	close_fork(int fd1, int fd2, t_exec *node, t_main *main)
{
	int i;

	i = 0;
	if (fd1 != node->infile.fd && fd1 > 1 && close(fd1) == -1)
	{
		i = 1;
	}
	if (fd2 > 1 && close(fd2) == -1)
	{
		i = 1;
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

// pid_t fork_process(t_main *main, int prevfd, int pipein, int pipeout);
pid_t	child_process(t_exec *node, int prev_fd, t_main *main, char **env)
{
	int		pipefd[2];
	pid_t	pid;

	if (prev_fd == -1 || pipe(pipefd) == -1)
		error_exit("Error : Pipe failed", EXIT_FAILURE, prev_fd);
	pid = fork();
	if (pid == -1)
	{
		// close_dup_failed(pipefd[1], pipefd[0], 0);
		error_exit("Error : Fork failed", EXIT_FAILURE, prev_fd);
	}
	if (pid == 0)
	{
		close(pipefd[0]);
		dup_process_child(main, node, prev_fd, pipefd[1]);
		close_fork(prev_fd, pipefd[1], node, main);
		do_cmd(main, node->cmd, env);
	}
	close(pipefd[1]);
	// close(prev_fd);
	return (pipefd[0]);
}

pid_t	last_child(t_exec *node, int prev_fd, t_main *main, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		// close_dup_failed(node->outfile.fd, -1, 0);
		error_exit("Error : Fork failed", EXIT_FAILURE, prev_fd);
	}
	if (pid == 0)
	{
		dup_process_child(main, node, prev_fd, main->std_out);
		close_fork(prev_fd, -1, node, main);
		do_cmd(main, node->cmd, env);
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

int	pipe_exec(t_main *main)
{
	t_exec	*node;
	char		**env;
	int			prev_fd;
	int			i;
	int			if_hd;
	pid_t		last_pid;

	i = 0;
	if_hd = 0;
	node = main->exec;
	prev_fd = node->infile.fd;
	env = env_to_tab(main);
	while (node->next != NULL)
	{
		prev_fd = child_process(node, prev_fd, main, env);
		if (prev_fd == -1)
			return (0);
		node = node->next;
		i++;
	}
	// access_out_check(main, prev_fd, node->outfile.fd, if_hd);
	last_pid = last_child(node, prev_fd, main, env);
	wait_child(last_pid);
	close(prev_fd);
	close_node(main);
	// reset_struct(NULL, main);
	return (0);
}
