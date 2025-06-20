#include "../includes/minishell.h"

static void	parse(t_main *shell, char *cmd)
{
	t_parse_error	errcode;

	errcode = tokenisation(shell, cmd);
	// printf("\nReturn tokenisation : %d\n", errcode);
	if (!check_parsing(shell, errcode))
		return ;
	// print_token_lst(shell->token, "\nToken lst before parsing :\n");
	errcode = parsing(&shell->exec, &shell->token);
	// printf("\nReturn create exec : %d\n", errcode);
	check_parsing(shell, errcode);
	// print_token_lst(shell->token, "\nToken lst after parsing :\n");
}

void	start_shell(t_main *shell)
{
	char	*rl;
	char	*line;

	while (1)
	{
		dup2(shell->std_in, STDIN_FILENO);
		dup2(shell->std_out, STDOUT_FILENO);
		if (isatty(fileno(stdin)))
		{
			rl = readline("> ");
		}
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
		// rl = readline("$> ");
		if (!rl)
		{
			exit_error_two_close(shell, (shell)->std_out, (shell)->std_in);;
			free_struct(shell);
			// prinetf("exit\n");
			return ;
		}
		add_history(rl);
		parse(shell, rl);
		check_input(shell);
		reset_struct(rl, shell);
		rl_on_new_line();
	}
	clear_history();
}

int	main(int ac, char **av, char **env)
{
	(void)av;
	t_main	*shell;

	if (ac == 1)
	{
		shell = init_minishell(env);
		start_shell(shell);
		free(shell);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
