/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:45:05 by karamire          #+#    #+#             */
/*   Updated: 2025/07/24 11:02:33 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	safe_close(int fd, t_shell *main)
{
	t_exec	*tmp;

	tmp = main->exec;
	while (tmp && fd != tmp->outfile.fd && fd != tmp->infile.fd)
	{
		tmp = tmp->next;
	}
	if (tmp == NULL && fd > 1)
	{
		if (close(fd) == -1)
		{
			exit_error_minishell(main, 2, "Close Error");
		}
	}
	return ;
}

void	wait_child(pid_t last, t_shell *main)
{
	int	status;
	int	sig;

	while (waitpid(last, &status, 0) > 0)
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
	while (wait(NULL) > 0)
		;
}

void	ignore_child_signal(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}
