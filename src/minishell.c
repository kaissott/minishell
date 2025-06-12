#include "../includes/minishell.h"

static void	parse(t_main **main_struct, char *cmd)
{
	t_parse_error	ret;

	ret = tokenisation(&(*main_struct)->env, &(*main_struct)->token,
			&(*main_struct)->error, cmd);
	printf("Return tokenisation : %d\n", ret);
	if (ret != ERR_NONE)
	{
		print_token_error_msg(ret, (*main_struct)->error.unexpected_token);
		(*main_struct)->error.error_type = 0;
		(*main_struct)->error.unexpected_token = 0;
		free_token_lst(&(*main_struct)->token);
	}
	else
	{
		print_token_lst((*main_struct)->token,
			"\nToken lst before parsing :\n");
		ret = create_exec_lst(&(*main_struct)->exec, &(*main_struct)->token);
		if (ret != ERR_NONE)
		{
			print_token_error_msg(ret, (*main_struct)->error.unexpected_token);
			(*main_struct)->error.error_type = 0;
			(*main_struct)->error.unexpected_token = 0;
			free_token_lst(&(*main_struct)->token);
		}
		printf("Return create exec : %d\n", ret);
		print_exec_lst((*main_struct)->exec, "Exec lst : \n");
		if ((*main_struct)->token)
		{
			printf("Token lst not empty after parsing <- error\n");
			free_token_lst(&(*main_struct)->token);
		}
		print_token_lst((*main_struct)->token, "Token lst after : \n");
		free_exec_lst(&(*main_struct)->exec);
	}
}

void	start_shell(t_main **main_struct)
{
	char	*rl;

	while (1)
	{
		rl = readline("$> ");
		if (!rl)
			return ;
		add_history(rl);
		parse(main_struct, rl);
		free(rl);
		rl_on_new_line();
	}
	clear_history();
	free_env_lst(&(*main_struct)->env);
}

int	main(int ac, char **av, char **env)
{
	t_main	*main_struct;

	(void)av;
	main_struct = ft_calloc(1, sizeof(t_main));
	if (!main_struct)
		return (EXIT_FAILURE);
	create_env_lst(&main_struct->env, env);
	// print_env_lst(main_struct->env, "ENV LST :\n");
	if (ac == 1)
	{
		start_shell(&main_struct);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
