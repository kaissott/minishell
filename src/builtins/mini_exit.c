/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 21:19:06 by kaissramire       #+#    #+#             */
/*   Updated: 2025/06/13 16:48:21 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (line[1] && line[1][0] != '\0')
	{
		exit_code = check_and_conv_exit_code(line, size);
		errno = exit_code;
		free_struct(main);
		exit(exit_code);
	}
	free_struct(main);
	exit(errno);
}
