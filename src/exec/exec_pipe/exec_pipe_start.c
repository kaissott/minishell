/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_start.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaissramirez <kaissramirez@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 18:59:00 by karamire          #+#    #+#             */
/*   Updated: 2025/07/18 00:45:37 by kaissramire      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

pid_t	last_child(t_exec *node, int prev_fd, t_main *main, char **env)
{
	pid_t	pid;

	if (node->infile.fd == -1 || node->outfile.fd == -1)
	{
		main->errcode = 1;
		return (1);
	}
	pid = fork();
	if (pid == -1)
	{
		free(env);
		error_fork(NULL, prev_fd, node, main);
	}
	if (pid == 0)
	{
		dup_process_child(main, node, prev_fd, main->std_out);
		close_fork(prev_fd, -1, node, main);
		if (node->cmd[0] != NULL)
			do_cmd(main, node->cmd, env);
	}
	return (pid);
}

pid_t	child_process(t_exec *node, int prev_fd, t_main *main, char **env)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
		error_pipe(prev_fd, node, main);
	if (node->infile.fd == -1 || node->outfile.fd == -1)
	{
		close(pipefd[1]);
		return (pipefd[0]);
	}
	pid = fork();
	if (pid == -1)
		error_fork(pipefd, prev_fd, node, main);
	if (pid == 0)
	{
		close(pipefd[0]);
		dup_process_child(main, node, prev_fd, pipefd[1]);
		close_fork(prev_fd, pipefd[1], node, main);
		if (node->cmd[0] != NULL)
			do_cmd(main, node->cmd, env);
	}
	safe_close(prev_fd, main);
	close(pipefd[1]);
	return (pipefd[0]);
}

int	pipe_exec(t_main *main)
{
	t_exec	*node;
	int		prev_fd;
	pid_t	last_pid;

	node = main->exec;
	prev_fd = node->infile.fd;
	main->env_tab = env_to_tab(main);
	while (node->next != NULL)
	{
		prev_fd = child_process(node, prev_fd, main, main->env_tab);
		if (prev_fd == -1)
			return (0);
		node = node->next;
	}
	last_pid = last_child(node, prev_fd, main, main->env_tab);
	close(prev_fd);
	close_node(main);
	wait_child(last_pid, main);
	free(main->env_tab);
	return (0);
}
