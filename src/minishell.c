#include "../includes/minishell.h"

static void	parse(t_exec **lst_exec, t_token **lst_token, t_error *error,
		char *cmd)
{
	if (tokenisation(lst_token, error, cmd) != ERR_NONE)
	{
		print_token_error_msg(error->error_type, error->unexpected_token);
		error->error_type = 0;
		error->unexpected_token = 0;
	}
	else
	{
		print_lst_token(*lst_token, "\nToken lst :\n");
		create_exec_lst(lst_exec, lst_token);
	}
}

void	start_shell(void)
{
	char	*rl;
	t_exec	*lst_exec;
	t_token	*lst_token;
	t_error	*error;

	lst_exec = NULL;
	lst_token = NULL;
	error = ft_calloc(1, sizeof(t_error));
	if (!error)
		print_token_error_msg(ERR_MALLOC, '\0');
	while (1)
	{
		rl = readline("$> ");
		if (*rl)
			add_history(rl);
		parse(&lst_exec, &lst_token, error, rl);
		free(rl);
		free_lst(&lst_exec);
		// free_lst_token(&lst_token);
		rl_on_new_line();
	}
	clear_history();
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	start_shell();
	return (EXIT_SUCCESS);
}
