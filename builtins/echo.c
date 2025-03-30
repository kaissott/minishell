/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 20:08:11 by karamire          #+#    #+#             */
/*   Updated: 2025/03/28 18:36:12 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	echo_flag(t_cmd *echo)
{
	int	i;

	i = 1;
	if (echo->flag[0] == '-')
	{
		while (echo->flag[i] != '\0')
		{
			if (echo->flag[i] != 'n')
				return (0);
			i++;
		}
	}
	return (1);
}

void	print_echo(t_cmd *echo, int i)
{
	char	*str;
	int		j;

	j = 0;
	if (i == 0 && echo->flag != NULL)
	{
		str = ft_strjoin(echo->flag, " ");
		str = ft_strjoin(str, echo->args);
	}
	else
		str = ft_strdup(echo->args);
	while (str[j])
	{
		if (str[j] == ' ')
		{
			while (str[j] == ' ')
				j++;
			write(1, " ", 1);
		}
			write(1, &str[j], 1);
			j++;
	}
	if (i == 1)
		write(1, "\n", 1);
	free(str);
}

int	mini_echo(t_cmd *echo)
{
	int	i;

	i = 0;
	if (echo_flag(echo) == 1)
		i = 1;
	print_echo(echo, i);
}
int	main(int ac, char **av)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	cmd->cmd = "echo";
	cmd->flag = av[1];
	cmd->args = av[2];
	mini_echo(cmd);
	return (0);
}
