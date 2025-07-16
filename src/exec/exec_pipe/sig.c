/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 00:46:57 by karamire          #+#    #+#             */
/*   Updated: 2025/07/16 23:24:07 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	my_handler(int sig)
{
	if (sig == SIGINT)
	{
		if (g_sig_mode == INTERACTIVE)
		{
			write(1, "\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		else if (g_sig_mode == HERE_DOC)
		{
			write(1, "\n", 1);
			g_sig_mode = INTERACTIVE;
		}
		else if (g_sig_mode == CHILD)
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
		g_sig_mode = INTERACTIVE;
		sa.sa_handler = my_handler;
		sigaction(SIGINT, &sa, NULL);
		sa.sa_handler = SIG_IGN;
		sigaction(SIGQUIT, &sa, NULL);
	}
	else if (mode == 1)
	{
		g_sig_mode = CHILD;
		sa.sa_handler = SIG_DFL;
		sigaction(SIGINT, &sa, NULL);
		sigaction(SIGQUIT, &sa, NULL);
	}
	else if (mode == 2)
	{
		sig_mode = HERE_DOC;
		sa.sa_handler = my_handler;
		sigaction(SIGINT, &sa, NULL);
		sa.sa_handler = SIG_IGN;
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
