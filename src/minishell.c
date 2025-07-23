/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 02:02:50 by ludebion          #+#    #+#             */
/*   Updated: 2025/07/23 16:49:24 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_sig_mode = INTERACTIVE;
int						i = 0;

static void	parse(t_shell *shell, char *cmd)
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

void	start_shell(t_shell *shell)
{
	char	*rl;
	char	*line;

	while (1)
	{
		init_sigaction(0);
		if (dup2(shell->std_in, STDIN_FILENO) == -1 || dup2(shell->std_out,
				STDOUT_FILENO) == -1)
			free_and_exit_error(shell, NULL, "Dup 2 failed", errno);
		if (isatty(fileno(stdin)))
			rl = readline("> ");
		else
		{
			rl = get_next_line(fileno(stdin));
			if (rl)
			{
				line = ft_strtrim(rl, "\n");
				free(rl);
				rl = line;
			}
		}
		if (!rl)
		{
			exit_error_two_close(shell, (shell)->std_out, (shell)->std_in);
			return ;
		}
		add_history(rl);
		parse(shell, rl);
		check_input(shell);
		reset_struct(rl, shell);
		i++;
		// rl_on_new_line();
	}
	clear_history();
}

int	main(int ac, char **av, char **env)
{
	t_shell	*shell;
	int		errcode;

	(void)av;
	if (ac > 1)
		return (EXIT_SUCCESS);
	shell = init_minishell(env);
	start_shell(shell);
	errcode = shell->errcode;
	free_struct(shell);
	free(shell);
	return (errcode);
}
