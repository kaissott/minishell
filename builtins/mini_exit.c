/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaissramirez <kaissramirez@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 21:19:06 by kaissramire       #+#    #+#             */
/*   Updated: 2025/05/13 00:31:15 by kaissramire      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

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
		while (exit[i] == '+')
			i++;
	}
	else if (exit[i] == '-')
	{
		while (exit[i] == '-')
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
			return (2);
		i++;
	}
	if (size > 2)
		return (1);
	exit_code = ft_atoll(exit[1], &error) % 256;
	if (error == -1)
	{
		numeric_argument_error("caca", exit);
	}
	return (exit_code);
}

int	mini_exit(char *line, t_main *main)
{
	char	**cmd;
	int		exit_code;
	int		size;

	exit_code = 0;
	cmd = ft_split(line, ' ');
	if (!cmd)
	{
		free(line);
		handle_error_exit(ERR_MALLOC, 12);
	}
	free(line);
	size = tab_size(cmd);
	if (cmd[1] && cmd[1][0] != '\0')
	{
		exit_code = check_and_conv_exit_code(cmd, size);
		errno = exit_code;
		free_env(main->mainenv);
		free(cmd[0]);
		free(cmd[1]);
		free(cmd);
		free(main);
		exit(exit_code);
	}
	exit(errno);
}
