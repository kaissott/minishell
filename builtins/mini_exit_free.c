/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:45:28 by kaissramire       #+#    #+#             */
/*   Updated: 2025/05/22 16:22:49 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"

void	free_tab_exit(char **args)
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
