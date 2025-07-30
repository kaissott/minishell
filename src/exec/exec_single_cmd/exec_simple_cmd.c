/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaissramirez <kaissramirez@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:40:24 by kaissramire       #+#    #+#             */
/*   Updated: 2025/07/30 16:24:57 by kaissramire      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void	exec_simple_cmd(t_shell *main)
{
	char	*env_path;
	char	*path;

	main->env_tab = env_to_tab(main);
	ultimate_path_check(main, main->exec->cmd);
	env_path = env_path_finding(main, main->env_tab);
	path = get_path(main, env_path, main->env_tab);
	if (!path)
	{
		if (!env_path && check_current_dir_exec(main, main->exec->cmd))
			return ;
		free(env_path);
		execve_err(main, main->env_tab, path, main->exec->cmd[0]);
		return ;
	}
	execve(path, main->exec->cmd, main->env_tab);
	execve_err(main, main->env_tab, path, main->exec->cmd[0]);
}

void	wait_simple_cmd(t_shell *main, pid_t pid)
{
	int		status;
	int		sig;
	bool	has_sig;

	has_sig = false;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		main->errcode = WEXITSTATUS(status);
	}
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGQUIT)
			write(2, "Quit (core dumped)\n", 20);
		if (sig == SIGINT)
			has_sig = true;
		main->errcode = 128 + sig;
	}
	if (has_sig == true)
		write(2, "\n", 1);
}

void	init_simple_cmd(t_shell *main)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		error_fork(NULL, -1, main->exec, main);
	ignore_child_signal();
	if (pid == 0)
	{
		init_sigaction_child();
		exit_error_two_close(main, main->std_in, main->std_out);
		exit_error_two_close(main, main->exec->infile.fd,
			main->exec->outfile.fd);
		exec_simple_cmd(main);
	}
	wait_simple_cmd(main, pid);
	return ;
}
