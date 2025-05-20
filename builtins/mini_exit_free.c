/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaissramirez <kaissramirez@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:45:28 by kaissramire       #+#    #+#             */
/*   Updated: 2025/05/20 19:25:47 by kaissramire      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"

void	free_tab(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

int	numeric_argument_error(char *error, char **args)
{
	ft_putstr_fd("exit\nbash: exit: ", 2);
	ft_putstr_fd(args[1], 2);
	ft_putstr_fd(ERR_NUM_ARG, 2);
	free_tab(args);
	exit(2);
}
