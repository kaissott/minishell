/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 00:46:57 by karamire          #+#    #+#             */
/*   Updated: 2025/08/27 17:40:39 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler_interactive(int sig)
{
	if (sig == SIGINT)
	{
		g_sig_mode = sig;
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	else
		g_sig_mode = sig;
}

void	handler_here_doc(int sig)
{
	if (sig == SIGINT)
	{
		g_sig_mode = sig;
		rl_replace_line("", 0);
		write(STDOUT_FILENO, "^C", 2);
		rl_done = 1;
		// rl_on_new_line();
	}
	else
		g_sig_mode = sig;
}

void	init_sigaction_hd(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = handler_here_doc;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

void	init_sigaction(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = handler_interactive;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

void	init_sigaction_child(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = SIG_DFL;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_DFL;
	sigaction(SIGQUIT, &sa, NULL);
}
