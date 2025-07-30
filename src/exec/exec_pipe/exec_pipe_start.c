/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_start.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 18:59:00 by karamire          #+#    #+#             */
/*   Updated: 2025/07/30 19:26:53 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static pid_t	check_child_stds(int pipefd[2], int prev_fd, t_shell *main)
{
	if (prev_fd > 2)
		ft_safe_close(&prev_fd, main);
	ft_safe_close(&pipefd[1], main);
	return (pipefd[0]);
}

static pid_t	last_child(t_exec *node, int prev_fd, t_shell *main, char **env)
{
	pid_t	pid;

	if (node->infile.fd == -1 || node->outfile.fd == -1)
	{
		main->errcode = 1;
		return (1);
	}
	pid = fork();
	if (pid == -1)
		error_fork(NULL, prev_fd, node, main);
	if (pid == 0)
	{
		init_sigaction_child();
		dup_process_child(main, node, prev_fd, main->std_out);
		ft_safe_close(&prev_fd, main);
		close_node(main);
		if (node->cmd[0] != NULL)
			do_cmd(main, node->cmd, env);
	}
	return (pid);
}

static int	handle_last_child(t_shell *main, t_exec *node, int prev_fd)
{
	pid_t	last_pid;
	int		has_sig;
	int		status;

	status = 0;
	has_sig = 0;
	last_pid = last_child(node, prev_fd, main, main->env_tab);
	ft_safe_close(&prev_fd, main);
	close_node(main);
	wait_child(last_pid, main, status, &has_sig);
	if (has_sig == 1)
		write(2, "\n", 1);
	free(main->env_tab);
	main->env_tab = NULL;
	return (0);
}

static pid_t	child_process(t_exec *node, int prev_fd, t_shell *main,
		char **env)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
		error_pipe(prev_fd, node, main);
	if (node->infile.fd == -1 || node->outfile.fd == -1)
		return (check_child_stds(pipefd, prev_fd, main));
	pid = fork();
	if (pid == -1)
		error_fork(pipefd, prev_fd, node, main);
	if (pid == 0)
	{
		init_sigaction_child();
		ft_safe_close(&pipefd[0], main);
		dup_process_child(main, node, prev_fd, pipefd[1]);
		close_fork(&prev_fd, &pipefd[1], node, main);
		if (node->cmd[0] != NULL)
			do_cmd(main, node->cmd, env);
	}
	ft_safe_close(&prev_fd, main);
	ft_safe_close(&pipefd[1], main);
	return (pipefd[0]);
}

int	pipe_exec(t_shell *main)
{
	t_exec	*node;
	int		prev_fd;

	node = main->exec;
	prev_fd = node->infile.fd;
	main->env_tab = env_to_tab(main);
	ignore_child_signal();
	while (node->next != NULL)
	{
		prev_fd = child_process(node, prev_fd, main, main->env_tab);
		if (prev_fd == -1)
			return (0);
		node = node->next;
	}
	return (handle_last_child(main, node, prev_fd));
}
