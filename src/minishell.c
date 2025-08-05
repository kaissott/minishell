/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 02:02:50 by ludebion          #+#    #+#             */
/*   Updated: 2025/07/30 21:33:32 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

volatile sig_atomic_t	g_sig_mode = 0;

static void	parse(t_shell *shell, const char *cmd)
{
	t_parse_error	errcode;

	errcode = tokenisation(shell, cmd);
	if (!check_parsing(shell, errcode, false))
		return ;
	errcode = expansion(shell);
	if (!check_parsing(shell, errcode, false))
		return ;
	errcode = word_splitting(shell);
	if (!check_parsing(shell, errcode, false))
		return ;
	errcode = parsing(shell);
	check_parsing(shell, errcode, true);
}

static char	*rl_check(t_shell *shell)
{
	char	*rl;

	rl = NULL;
	if (isatty(STDIN_FILENO))
	{
		rl = readline("> ");
		if (shell->errcode < 3 && g_sig_mode > 0)
			shell->errcode = g_sig_mode + 128;
	}
	return (rl);
}

static void	start_shell(t_shell *shell)
{
	char	*rl;

	rl = NULL;
	while (1)
	{
		init_sigaction();
		if (dup2(shell->std_in, STDIN_FILENO) == -1 || dup2(shell->std_out,
				STDOUT_FILENO) == -1)
			free_and_exit_error(shell, NULL, "Dup 2 failed", errno);
		rl = rl_check(shell);
		if (!rl)
			return (exit_error_two_close(shell, &(shell)->std_out,
					&(shell)->std_in));
		g_sig_mode = 0;
		if (!is_ascii_printable(rl))
		{
			free(rl);
			continue ;
		}
		add_history(rl);
		parse(shell, rl);
		check_input(shell);
		reset_struct(rl, shell);
	}
	rl_clear_history();
}

int	main(int ac, char **av, char **env)
{
	t_shell	*shell;
	int		errcode;

	(void)av;
	if (ac > 1)
		return (EXIT_FAILURE);
	shell = init_minishell(env);
	start_shell(shell);
	errcode = shell->errcode;
	free_struct(shell);
	free(shell);
	return (errcode);
}
