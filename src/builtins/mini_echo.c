#include "../../includes/minishell.h"

bool	check_echo_flag(char **tab)
{
	int	i;

	i = 1;
	if (tab[1])
	{
		if (tab[1][0] == '-')
		{
			while (tab[1][i] == 'n')
			{
				i++;
				if (tab[1][i] == '\0')
					return (true);
			}
		}
	}
	return (false);
}

void	print_echo_with_flag(t_main *main, char **tab)
{
	int	i;

	i = 2;
	while (tab[i])
	{
		if (ft_putstr_fd(tab[i], STDOUT_FILENO) == -1)
			free_and_exit_error(main, ERR_WRITE, errno);
		i++;
		if (tab[i])
		{
			if (write(STDOUT_FILENO, " ", 1) == -1)
				free_and_exit_error(main, ERR_WRITE, errno);
		}
	}
}

void	print_echo_without_flag(t_main *main, char **tab)
{
	int	i;

	i = 1;
	while (tab[i])
	{
		if (ft_putstr_fd(tab[i], STDOUT_FILENO) == -1)
			free_and_exit_error(main, ERR_WRITE, errno);
		i++;
		if (tab[i])
		{
			if (write(STDOUT_FILENO, " ", 1) == -1)
				free_and_exit_error(main, ERR_WRITE, errno);
		}
	}
	if (write(STDOUT_FILENO, "\n", 1) == -1)
		free_and_exit_error(main, ERR_WRITE, errno);
}

bool	mini_echo(t_main *main)
{
	char	**tab;

	tab = main->exec->cmd;
	if (check_echo_flag(tab) == true)
		print_echo_with_flag(main, tab);
	else
		print_echo_without_flag(main, tab);
	return (true);
}
