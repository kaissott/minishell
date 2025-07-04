#include "../includes/minishell.h"
#include <signal.h>

volatile sig_atomic_t	sig_mode = INTERACTIVE;

static void	parse(t_main *shell, char *cmd)
{
	t_parse_error	errcode;

	// printf("\nERRCODE BEFORE ALL PARSE : %d\n", shell->errcode);
	errcode = tokenisation(shell, cmd);
	// printf("\nReturn tokenisation : %d\n", errcode);
	if (!check_parsing(shell, errcode, false))
		return ;
	// print_token_lst(shell->token, "\nToken lst after tokenisation :\n");
	errcode = expansion(shell);
	// printf("\nReturn expansion : %d\n", errcode);
	if (!check_parsing(shell, errcode, false))
		return ;
	// print_token_lst(shell->token, "\nToken lst after expansion :\n");
	errcode = word_splitting(shell);
	// printf("\nReturn word splitting : %d\n", errcode);
	if (!check_parsing(shell, errcode, false))
		return ;
	// print_token_lst(shell->token, "\nToken lst after word splitting :\n");
	errcode = parsing(shell);
	// printf("\nReturn parsing : %d\n", errcode);
	check_parsing(shell, errcode, true);
	// print_token_lst(shell->token, "\nToken lst after parsing :\n");
	// print_exec_lst(shell->exec, "EXEC LST AFTER PARSING :\n");
}

void	start_shell(t_main *shell)
{
	char	*rl;
	char	*line;

	while (1)
	{
		init_sigaction(0);
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
			exit_error_two_close(shell, (shell)->std_out, (shell)->std_in);
			return ;
		}
		if (rl[0] == '\0')
		{
			free(rl);
			continue ;
		}
		add_history(rl);
		parse(shell, rl);
		check_input(shell);
		reset_struct(rl, shell);
		// rl_on_new_line();
	}
	clear_history();
}



int	main(int ac, char **av, char **env)
{
	t_main	*shell;
	int		errcode;

	(void)av;
	shell = init_minishell(env);
	start_shell(shell);
	errcode = shell->errcode;
	free_struct(shell);
	free(shell);
	return (errcode);
	// }
	return (EXIT_FAILURE);
}
