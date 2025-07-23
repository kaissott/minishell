/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 20:08:11 by karamire          #+#    #+#             */
/*   Updated: 2025/07/23 00:25:03 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_echo_flag(char *tab)
{
	int	i;

	i = 1;
	if (tab)
	{
		if (tab[0] == '-')
		{
			while (tab[i] == 'n')
			{
				i++;
				if (tab[i] == '\0')
					return (true);
			}
		}
	}
	return (false);
}

void	print_echo_with_flag(t_main *main, char **tab)
{
	int	i;
	int	j;

	j = 0;
	i = 1;
	while (tab[i])
	{
		if (j == 0 && check_echo_flag(tab[i]) == true)
			i++;
		else
		{
			j = 1;
			ft_putstr_fd(tab[i], STDOUT_FILENO);
			i++;
			if (tab[i])
			{
				ft_putchar_fd(' ', STDOUT_FILENO);
			}
		}
	}
}

void	print_echo_without_flag(t_main *main, char **tab)
{
	int	i;

	i = 1;
	while (tab[i])
	{
		ft_putstr_fd(tab[i], STDOUT_FILENO);
		i++;
		if (tab[i])
			write(STDOUT_FILENO, " ", 1);
	}
	write(STDOUT_FILENO, "\n", 1);
}

bool	mini_echo(t_main *main, char **cmd)
{
	if (check_echo_flag(cmd[1]) == true)
		print_echo_with_flag(main, cmd);
	else
		print_echo_without_flag(main, cmd);
	return (true);
}
