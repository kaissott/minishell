/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 00:46:57 by karamire          #+#    #+#             */
/*   Updated: 2025/07/04 02:40:31 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	mon_handler(int sig)
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
			printf("child CTRL C");
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
		sa.sa_handler = mon_handler;
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
