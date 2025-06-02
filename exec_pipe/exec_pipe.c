/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:45:05 by karamire          #+#    #+#             */
/*   Updated: 2025/06/02 20:19:49 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 18:31:58 by karamire          #+#    #+#             */
/*   Updated: 2025/06/02 16:40:52 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"

pid_t	child_process(t_main *main, char **cmd, char **env, int prev_fd)
{
	int		pipefd[2];
	pid_t	pid;

	// printf("%s\n", cmd[0]);
	if (prev_fd == -1 || pipe(pipefd) == -1)
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
		{
			close_dup_failed(pipefd[1], prev_fd, 1);
		}
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			close_dup_failed(pipefd[1], prev_fd, 1);
		close(pipefd[1]);
		close(prev_fd);
		do_cmd(main, cmd, env);
		dprintf(2, "exec");
	}
	close(pipefd[1]);
	close(prev_fd);
	return (pipefd[0]);
}

pid_t	last_child(t_lst_node *node, int prev_fd, t_main *main, char **env)
{
	pid_t	pid;

	printf("%d\n", node->outfile.fd);
	pid = fork();
	if (pid == -1)
	{
		close_dup_failed(node->outfile.fd, -1, 0);
		error_exit("Error : Fork failed", EXIT_FAILURE, prev_fd);
	}
	if (pid == 0)
	{
		if (prev_fd != -1)
		{
			if (dup2(prev_fd, STDIN_FILENO) == -1)
				close_dup_failed(node->outfile.fd, prev_fd, 1);
			close(prev_fd);
		}
		if (dup2(node->outfile.fd, STDOUT_FILENO) == -1)
			close_dup_failed(node->outfile.fd, prev_fd, 1);
		close(node->outfile.fd);
		do_cmd(main, node->cmd, env);
		dprintf(2, "exec");
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
	t_lst_node	*node;
	char		**env;
	int			prev_fd;
	int			i;
	int			if_hd;
	pid_t		last_pid;

	i = 0;
	node = main->node;
	prev_fd = node->infile.fd;
	env = env_to_tab(main);
	while (node->next != NULL)
	{
		prev_fd = child_process(main, node->cmd, env, prev_fd);
		if (prev_fd == -1)
			return (0);
		node = node->next;
	}
	// access_out_check(main, prev_fd, node->outfile.fd, if_hd);
	printf("%s\n", node->cmd[0]);
	last_pid = last_child(node, prev_fd, main, env);
	close_fd(prev_fd, node->outfile.fd, if_hd);
	wait_child(last_pid);
	return (0);
}
