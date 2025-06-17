#include "../includes/minishell.h"

static void	parse(t_main *shell, char *cmd)
{
	t_parse_error	errcode;

	errcode = tokenisation(shell, cmd);
	printf("\nReturn tokenisation : %d\n", errcode);
	if (!check_parsing(shell, errcode))
		return ;
	print_token_lst(shell->token, "\nToken lst before parsing :\n");
	errcode = parsing(&shell->exec, &shell->token);
	printf("\nReturn create exec : %d\n", errcode);
	check_parsing(shell, errcode);
	print_token_lst(shell->token, "\nToken lst after parsing :\n");
}

void	start_shell(t_main *shell)
{
	char	*rl;
	int		std_out;
	int		std_in;
	char	*line;
	char	*trimmed;

	std_out = dup(STDOUT_FILENO);
	std_in = dup(STDERR_FILENO);
	while (1)
	{
		dup2(std_in, STDIN_FILENO);
		dup2(std_out, STDOUT_FILENO);
		// if (isatty(fileno(stdin)))
		// 	rl = readline("$> ");
		// else
		// {
		// 	rl = get_next_line(fileno(stdin));
		// 	if (rl)
		// 	{
		// 		trimmed = ft_strtrim(rl, "\n");
		// 		free(rl);
		// 		rl = trimmed;
		// 	}
		// }
		printf("shell->errcode before parsing : %d\n", shell->errcode);
		rl = readline("$> ");
		if (!rl)
		{
			clear_and_exit(shell, ERR_NONE);
			return ;
		}
		add_history(rl);
		parse(shell, rl);
		printf("shell->errcode after parsing : %d\n", shell->errcode);
		// check_input(shell);
		free_exec_lst(&shell->exec);
		free(rl);
		rl = NULL;
		rl_on_new_line();
	}
	clear_history();
}

int	main(int ac, char **av, char **env)
{
	t_main	*shell;
	size_t	i;

	i = 0;
	// while (env[i])
	// {
	// 	printf("\nenv[%zu] :\n\t[%s]\n", i, env[i]);
	// 	i++;
	// }
	(void)av;
	shell = ft_calloc(1, sizeof(t_main));
	if (!shell)
		return (EXIT_FAILURE);
	check_env_available(env, shell);
	if (ac == 1)
	{
		start_shell(shell);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
