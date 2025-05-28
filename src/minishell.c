#include "../includes/minishell.h"

void	start_shell(void)
{
	char		*rl;
	t_lst_node	*lst;
	t_token		*lst_token;

	lst = NULL;
	lst_token = NULL;
	while (1)
	{
		rl = readline("$> ");
		if (*rl)
			add_history(rl);
		parse(&lst, &lst_token, rl);
		free(rl);
		free_lst(&lst);
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
