#include "../../includes/minishell.h"

int	tab_size(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int	parse_sign(char *exit)
{
	int	i;

	i = 0;
	if (exit[i] == '+')
	{
			i++;
	}
	else if (exit[i] == '-')
	{
			i++;
	}
	return (i);
}

int	check_and_conv_exit_code(char **exit, int size)
{
	long long	exit_code;
	int			error;
	int			i;

	i = 0;
	error = 0;
	i = parse_sign(&exit[1][i]);
	while (exit[1][i])
	{
		if (ft_isdigit(exit[1][i]) == 0)
			numeric_argument_error("caca", exit);
		i++;
	}
	if (size > 2)
		return (1);
	exit_code = ft_atoll(exit[1], &error) % 256;
	if (error == -1 || exit[1][0] == '\0')
		numeric_argument_error("caca", exit);
	return (exit_code);
}

int	mini_exit(char **line, t_main *main)
{
	int	exit_code;
	int	size;
	int	i;

	i = 0;
	exit_code = 0;
	size = tab_size(line);

	// if (line[2])
	// {
	// 	while(line[2][i])
	// 	{
	// 		if (line[2][i] == '\0')
	// 		{
	// 			ft_putendl_fd("bash: exit: too many arguments", 2);
	// 			main->errcode = 1;
	// 			return(0);
	// 		}
	// 		if (!ft_isdigit(line[2][i]))
	// 			break;
	// 		i++;
	// 	}

	// }
	if (line[1])
	{
		exit_code = check_and_conv_exit_code(line, size);
		if (line[2])
		{
			ft_putendl_fd("bash: exit: too many arguments", 2);
			main->errcode = 1;
	 		return(0);
		}
		free_struct(main);
		exit(exit_code);
	}
	free_struct(main);
	exit(0);
}
