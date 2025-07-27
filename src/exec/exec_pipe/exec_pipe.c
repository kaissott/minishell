/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaissramirez <kaissramirez@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:45:05 by karamire          #+#    #+#             */
/*   Updated: 2025/07/27 06:17:17 by kaissramire      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	safe_close(int fd, t_shell *main)
{
	t_exec	*tmp;

	tmp = main->exec;
	while (tmp && fd != tmp->outfile.fd && fd != tmp->infile.fd)
	{
		tmp = tmp->next;
	}
	if (tmp == NULL && fd > 1)
		return (1);
	return (0);
}

void	ft_close(t_shell *main, int fd, int fd2, int fd3)
{
	if (fd > -1 && safe_close(fd, main))
	{
		if (close(fd) == -1)
		{
			if (fd2 > -1)
				close(fd2);
			if (fd3 > -1)
				close(fd3);
			free_and_exit_error(main, NULL, "Close Failed", 2);
		}
	}
}

void	wait_child(pid_t last, t_shell *main)
{
	int		status;
	int		sig;
	pid_t	w_child;
	bool	has_sig;

	status = 0;
	has_sig = false;
	while (1)
	{
		w_child = waitpid(-1, &status, 0);
		if (w_child <= 0)
			break ;
		if (WIFEXITED(status))
		{
			if (w_child == last)
				main->errcode = WEXITSTATUS(status);
		}
		else if (WIFSIGNALED(status))
		{
			sig = WTERMSIG(status);
			if (sig == SIGQUIT)
				write(2, "Quit (core dumped)\n", 20);
			if (sig == SIGINT)
				has_sig = true;
			if (w_child == last)
				main->errcode = 128 + sig;
		}
	}
	if (has_sig == true)
		write(2, "\n", 1);
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
