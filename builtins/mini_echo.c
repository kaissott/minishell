/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaissramirez <kaissramirez@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 20:08:11 by karamire          #+#    #+#             */
/*   Updated: 2025/05/08 21:32:56 by kaissramire      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

int	echo_flag(t_cmd *echo)
{
	int	i;

	i = 1;
	if (echo->flag != NULL && echo->flag[0] == '-')
	{
		while (echo->flag[i] != '\0')
		{
			if (echo->flag[i] != 'n')
				return (0);
			i++;
		}
		if (echo->flag[i] == '\0')
			return (1);
	}
	return (0);
}

void	print_echo_with_flag(t_cmd *echo)
{
	int	j;
	int	i;

	j = 0;
	while (echo->args[j] != NULL)
	{
		i = 0;
		while (echo->args[j][i] != '\0')
		{
			write(1, &echo->args[j][i], 1);
			i++;
			if (echo->args[j][i] == '\0' && echo->args[j + 1] != NULL)
				write(1, " ", 1);
		}
		j++;
	}
}

void	print_echo(t_cmd *echo)
{
	int	j;
	int	i;

	j = 0;
	while (echo->flag != NULL && echo->flag[j])
	{
		write(1, &echo->flag[j], 1);
		j++;
	}
	j = 0;
	while (echo->args[j] != NULL)
	{
		i = 0;
		write(1, " ", 1);
		while (echo->args[j][i] != '\0')
		{
			write(1, &echo->args[j][i], 1);
			i++;
		}
		j++;
	}
	write(1, "\n", 1);
}

int	mini_echo(t_cmd *echo)
{
	int	i;

	i = 0;
	if (echo_flag(echo) == 1)
	{
		print_echo_with_flag(echo);
		printf("il y a flag\n");
	}
	else
	{
		print_echo(echo);
	}
	return (1);
}
int	main(void)
{
	t_cmd	*echo;

	echo = malloc(sizeof(t_cmd));
	echo->cmd = "echo";
	echo->flag = "-n";
	echo->args = "coucou";
}
