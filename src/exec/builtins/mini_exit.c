/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 17:38:23 by karamire          #+#    #+#             */
/*   Updated: 2025/07/23 10:04:02 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	tab_size(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

static int	parse_sign(char *exit)
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

int	check_and_conv_exit_code(char **exit, int size, t_shell *main)
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
			numeric_argument_error(exit, main);
		i++;
	}
	if (size > 2)
		return (1);
	exit_code = ft_atoll(exit[1], &error) % 256;
	if (error == -1 || exit[1][0] == '\0')
		numeric_argument_error(exit, main);
	return (exit_code);
}

int	mini_exit(char **line, t_shell *main)
{
	int	exit_code;
	int	size;

	exit_code = 0;
	size = tab_size(line);
	if (line[1])
	{
		exit_code = check_and_conv_exit_code(line, size, main);
		if (line[2])
		{
			ft_putendl_fd("bash: exit: too many arguments", 2);
			main->errcode = 1;
			return (0);
		}
		exit_minishell(main, exit_code);
	}
	exit_minishell(main, 0);
	return (0);
}
