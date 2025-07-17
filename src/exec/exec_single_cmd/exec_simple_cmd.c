/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:40:24 by kaissramire       #+#    #+#             */
/*   Updated: 2025/07/17 23:49:00 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void	exec_simple_cmd(t_main *main)
{
	char	*env_path;
	char	*path;

	main->env_tab = env_to_tab(main);
	ultimate_path_check(main, main->exec->cmd);
	env_path = env_path_finding(main, main->env_tab);
	path = get_path(main, env_path, main->env_tab);
	if (!path)
	{
		if (!env_path && check_current_dir_exec(main))
			return ;
		free(path);
		free(env_path);
		execve_err(main, main->env_tab, path, main->exec->cmd[0]);
		return ;
	}
	execve(path, main->exec->cmd, main->env_tab);
	execve_err(main, main->env_tab, path, main->exec->cmd[0]);
}

void	wait_simple_cmd(t_main *main, pid_t pid)
{
	int	status;
	int	sig;

	while (waitpid(pid, &status, 0) > 0)
		;
	if (WIFEXITED(status))
		main->errcode = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGQUIT)
			write(2, "Quit (core dumped)\n", 20);
		if (sig == SIGINT)
			write(2, "\n", 1);
		main->errcode = 128 + sig;
	}
}
void	init_simple_cmd(t_main *main)
{
	pid_t	pid;
	int		status;
	int		sig;

	g_sig_mode = CHILD;
	pid = fork();
	if (pid == -1)
		error_fork(NULL, -1, main->exec, main);
	if (pid == 0)
	{
		init_sigaction(1);
		exit_error_two_close(main, main->std_in, main->std_out);
		exit_error_two_close(main, main->exec->infile.fd,
			main->exec->outfile.fd);
		exec_simple_cmd(main);
	}
	wait_simple_cmd(main, pid);
	return ;
}
