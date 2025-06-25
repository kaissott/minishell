
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 20:08:11 by karamire          #+#    #+#             */
/*   Updated: 2025/06/16 00:16:00 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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
			if (ft_putstr_fd(tab[i], STDOUT_FILENO) == -1)
				free_and_exit_error(main, NULL, ERR_WRITE, errno);
			i++;
			if (tab[i])
			{
				if (write(STDOUT_FILENO, " ", 1) == -1)
					free_and_exit_error(main, NULL, ERR_WRITE, errno);
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
		if (ft_putstr_fd(tab[i], STDOUT_FILENO) == -1)
			free_and_exit_error(main, NULL, ERR_WRITE, errno);
		i++;
		if (tab[i])
		{
			if (write(STDOUT_FILENO, " ", 1) == -1)
				free_and_exit_error(main, NULL, ERR_WRITE, errno);
		}
	}
	if (write(STDOUT_FILENO, "\n", 1) == -1)
		free_and_exit_error(main, NULL, ERR_WRITE, errno);
}

bool	mini_echo(t_main *main, char **cmd)
{
	if (check_echo_flag(cmd[1]) == true)
		print_echo_with_flag(main, cmd);
	else
		print_echo_without_flag(main, cmd);
	return (true);
}
