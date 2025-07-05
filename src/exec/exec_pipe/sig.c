/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luca <luca@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 00:46:57 by karamire          #+#    #+#             */
/*   Updated: 2025/07/05 06:05:49 by luca             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	my_handler(int sig)
{
	if (sig == SIGINT)
	{
		if (sig_mode == INTERACTIVE)
		{
			write(1, "\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		else if (sig_mode == HERE_DOC)
			printf("HD CTRL C");
		else if (sig_mode == CHILD)
			;
	}
}

void	init_sigaction(int mode)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (mode == 0)
	{
		sig_mode = INTERACTIVE;
		sa.sa_handler = my_handler;
		sigaction(SIGINT, &sa, NULL);
		sa.sa_handler = SIG_IGN;
		sigaction(SIGQUIT, &sa, NULL);
	}
	else if (mode == 1)
	{
		sig_mode = CHILD;
		sa.sa_handler = SIG_DFL;
		sigaction(SIGINT, &sa, NULL);
		sigaction(SIGQUIT, &sa, NULL);
	}
}

// int	main(void)
// {
// 	signal(SIGINT, mon_handler);
// 	signal(SIGQUIT, mon_handler);
// 	while (1)
// 		;
// }
