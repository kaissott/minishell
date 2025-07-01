/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:45:05 by karamire          #+#    #+#             */
/*   Updated: 2025/07/01 18:59:49 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	execve_err(t_main *main, char **env, char *path, char *cmd)
{
	ft_putstr_fd("bash: ", 2);
	// ft_putstr_fd(cmd, 2);
	// ft_putstr_fd("caca", 2)cl;
	perror(cmd);
	if (env)
		free(env);
	if (path != NULL)
		free(path);
	exit_error_minishell(main, 127, NULL);
}
void	safe_close(int fd, t_main *main)
{
	t_exec	*tmp;

	tmp = main->exec;
	while (tmp && fd != tmp->outfile.fd && fd != tmp->infile.fd)
	{
		tmp = tmp->next;
	}
	if (tmp == NULL && fd > 1)
		close(fd);
	return ;
}

void	close_fork(int fd1, int fd2, t_exec *node, t_main *main)
{
	int	i;

	i = 0;
	if (fd1 != node->infile.fd && fd1 > 1 && close(fd1) == -1)
	{
		i = 1;
		dprintf(2, "ici");
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
	if (pipefd == NULL)
	{
		close_fork(prevfd, -1, node, main);
		free_struct(main);
		free(main);
	}
	else
	{
		if (pipefd[0] > 1 && close(pipefd[0]) == -1)
		{
			return ;
		}
		close_fork(prevfd, pipefd[1], node, main);
		free_struct(main);
		free(main);
	}
	exit(errno);
}

pid_t	child_process(t_exec *node, int prev_fd, t_main *main, char **env)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
		error_exit("Error : Pipe failed", EXIT_FAILURE, prev_fd);
	pid = fork();
	if (pid == -1)
	{
		free(env);
		error_fork(pipefd, prev_fd, node, main);
	}
	if (pid == 0)
	{
		if (node->cmd[0] == NULL)
			exit(1);
		close(pipefd[0]);
		dup_process_child(main, node, prev_fd, pipefd[1]);
		close_fork(prev_fd, pipefd[1], node, main);
		do_cmd(main, node->cmd, env);
	}
	safe_close(prev_fd, main);
	close(pipefd[1]);
	return (pipefd[0]);
}

pid_t	last_child(t_exec *node, int prev_fd, t_main *main, char **env)
{
	pid_t	pid;

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
		do_cmd(main, node->cmd, env);
	}
	return (pid);
}

void	wait_child(pid_t last, t_main *main)
{
	int	status;

	while (waitpid(last, &status, 0) > 0)
	{
		if (WIFEXITED(status) && WEXITSTATUS(status) == 127)
			main->errcode = 127;
		if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
			main->errcode = 1;
	}
	while (wait(NULL) > 0)
		;
}

int	pipe_exec(t_main *main)
{
	t_exec	*node;
	int		prev_fd;
	pid_t	last_pid;

	node = main->exec;
	prev_fd = node->infile.fd;
	main->envtab = env_to_tab(main);
	while (node->next != NULL)
	{
		prev_fd = child_process(node, prev_fd, main, main->envtab);
		if (prev_fd == -1)
			return (0);
		node = node->next;
	}
	// access_out_check(main, prev_fd, node->outfile.fd, if_hd);
	last_pid = last_child(node, prev_fd, main, main->envtab);
	close(prev_fd);
	close_node(main);
	wait_child(last_pid, main);
	free(main->envtab);
	return (0);
}
