/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:45:05 by karamire          #+#    #+#             */
/*   Updated: 2025/07/02 19:00:32 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	execve_err(t_main *main, char **env, char *path, char *cmd)
{
	ft_putstr_fd("bash: ", 2);
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
		dprintf(2, "ici %s\n", node->cmd[0]);
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
	ft_putendl_fd("Fork failed", 2);
	if (pipefd == NULL)
	{
		close_fork(prevfd, -1, node, main);
		if (main->env_tab)
			free(main->env_tab);
		free_struct(main);
		free(main);
	}
	else
	{
		if (pipefd[0] > 1 && close(pipefd[0]) == -1)
			perror("close");
		if (main->env_tab)
			free(main->env_tab);;
		close_fork(prevfd, pipefd[1], node, main);
		free_struct(main);
		free(main);
	}
	exit(errno);
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

