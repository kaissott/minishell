/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaissramirez <kaissramirez@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 20:08:11 by karamire          #+#    #+#             */
/*   Updated: 2025/05/26 17:17:14 by kaissramire      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"

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

void	print_echo_with_flag(char **tab)
{
	int	i;

	i = 2;
	while (tab[i])
	{
		ft_putstr_fd(tab[i], 1);
		i++;
		if (tab[i])
			write(1, " ", 1);
	}
}

void	print_echo_without_flag(char **tab)
{
	int	i;

	i = 1;
	while (tab[i])
	{
		ft_putstr_fd(tab[i], 1);
		i++;
		if (tab[i])
			write(1, " ", 1);
	}
	write(1, "\n", 1);
}

int	mini_echo(t_main *main)
{
	char	**tab;

	tab = ft_split(main->node->cmd, ' ');
	if (check_echo_flag(tab) == true)
		print_echo_with_flag(tab);
	else
		print_echo_without_flag(tab);
}
