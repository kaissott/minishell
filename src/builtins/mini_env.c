#include "../../includes/minishell.h"

bool	env_print(t_main *main)
{
	t_env	*temp;

	temp = main->env;
	while (temp)
	{
		if (ft_putstr_fd(temp->env, STDOUT_FILENO) == -1)
			free_and_exit_error(main, ERR_WRITE, errno);
		if (write(STDOUT_FILENO, "\n", 1) == -1)
			free_and_exit_error(main, ERR_WRITE, errno);
		temp = temp->next;
	}
	return (true);
}
