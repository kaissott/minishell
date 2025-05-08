/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaissramirez <kaissramirez@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 21:19:06 by kaissramire       #+#    #+#             */
/*   Updated: 2025/05/09 01:42:43 by kaissramire      ###   ########.fr       */
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

int	check_and_conv_exit_code(char *exit, int size)
{
	long long	exit_code;
	int			error;
	int			i;

	i = 0;
	error = 0;
	i = parse_sign(&exit[i]);
	while (exit[i])
	{
		if (ft_isdigit(exit[i]) == 0)
			return (2);
		i++;
	}
	if (size > 2)
		return (1);
	exit_code = ft_atoll(exit, &error) % 256;
	if (error == -1)
	{
		exit_code = 2;
	}
	return (exit_code);
}

int	mini_exit(char *line)
{
	char	**cmd;
	int		exit_code;
	int		size;

	exit_code = 0;
	cmd = ft_split(line, ' ');
	size = tab_size(cmd);
	if (cmd[1])
		exit_code = check_and_conv_exit_code(cmd[1], size);
	exit(exit_code);
}
