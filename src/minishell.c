#include "../includes/minishell.h"

static void	parse(t_env **env_lst, char *cmd)
{
	t_exec	*exec_lst;
	t_token	*token_lst;
	t_error	*error;

	exec_lst = NULL;
	token_lst = NULL;
	error = ft_calloc(1, sizeof(t_error));
	if (!error)
		print_token_error_msg(ERR_MALLOC, '\0');
	if (tokenisation(env_lst, &token_lst, error, cmd) != ERR_NONE)
	{
		print_token_error_msg(error->error_type, error->unexpected_token);
		error->error_type = 0;
		error->unexpected_token = 0;
	}
	else
	{
		print_token_lst(token_lst, "\nToken lst before parsing :\n");
		if (create_exec_lst(&exec_lst, &token_lst) != ERR_NONE)
		{
			print_token_error_msg(error->error_type, error->unexpected_token);
			error->error_type = 0;
			error->unexpected_token = 0;
		}
		print_lst(exec_lst, "Exec lst : \n");
		print_token_lst(token_lst, "Token lst after : \n");
		// free_token_lst(token_lst);
		free_exec_lst(&exec_lst);
	}
}

void	start_shell(char **env)
{
	char	*rl;
	t_env	*env_lst;

	env_lst = NULL;
	create_env_lst(&env_lst, env);
	// print_env_lst(env_lst, "ENV LST :\n");
	while (1)
	{
		rl = readline("$> ");
		if (!rl)
			return ;
		add_history(rl);
		parse(&env_lst, rl);
		free(rl);
		rl_on_new_line();
	}
	clear_history();
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	start_shell(env);
	return (EXIT_SUCCESS);
}
