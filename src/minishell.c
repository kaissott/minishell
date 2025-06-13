#include "../includes/minishell.h"

static void	parse(t_main **main_struct, char *cmd)
{
	t_parse_error	ret;

	ret = tokenisation(&(*main_struct)->env, &(*main_struct)->token,
			&(*main_struct)->error, cmd);
	printf("\nReturn tokenisation : %d\n", ret);
	if (ret != ERR_NONE)
	{
		clear_and_exit(*main_struct, ret);
		return ;
	}
	else
	{
		print_token_lst((*main_struct)->token,
			"\nToken lst before parsing :\n");
		ret = parsing(&(*main_struct)->exec, &(*main_struct)->token);
		printf("\nReturn create exec : %d\n", ret);
		if (ret != ERR_NONE)
		{
			clear_and_exit(*main_struct, ret);
			return ;
		}
		print_exec_lst((*main_struct)->exec, "Exec lst : \n");
		if ((*main_struct)->token)
		{
			printf("Token lst not empty after parsing <- error\n");
			clear_and_exit(*main_struct, ret);
			return ;
		}
		print_token_lst((*main_struct)->token, "Token lst after : \n");
		free_main_struct(main_struct);
		return ;
	}
}

void	start_shell(t_main **main_struct)
{
	char	*rl;

	while (1)
	{
		dprintf(2, "caca\n");
		rl = readline("$> ");
		if (!rl)
		{
			clear_and_exit(*main_struct, ERR_NONE);
			return ;
		}
		add_history(rl);
		parse(main_struct, rl);
		free(rl);
		rl_on_new_line();
	}
	clear_history();
}

int	main(int ac, char **av, char **env)
{
	t_main	*main_struct;

	(void)av;
	main_struct = ft_calloc(1, sizeof(t_main));
	if (!main_struct)
		return (EXIT_FAILURE);
	// if (!create_env_lst(&main_struct->env, env))
	// {
	// 	printf("error in env lst\n");
	// 	free_env_lst(&main_struct->env);
	// 	// free(main_struct);
	// 	// return (EXIT_FAILURE);
	// }
	check_env_available(env, main_struct);
	dprintf(2, "%s\n", main_struct->env->env);
	// else print_env_lst(main_struct->env, "ENV LST :\n");
	if (ac == 1)
	{
		start_shell(&main_struct);
		free_env_lst(&main_struct->env);
		free(main_struct);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
