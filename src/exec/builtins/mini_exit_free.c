#include "../../../includes/minishell.h"

void	free_tab_exit(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

int	numeric_argument_error(char *error, char **args)
{
	ft_putstr_fd("exit\nbash: exit: ", 2);
	ft_putstr_fd(args[1], 2);
	ft_putstr_fd(ERR_NUM_ARG, 2);
	free_tab_exit(args);
	exit(2);
}
