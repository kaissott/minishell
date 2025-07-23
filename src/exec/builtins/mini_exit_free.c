/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 17:38:27 by karamire          #+#    #+#             */
/*   Updated: 2025/07/23 00:25:03 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	exit_minishell(t_main *main, int exitcode)
{
	close_node(main);
	free_struct(main);
	close(main->std_in);
	close(main->std_out);
	free(main);
	exit(exitcode);
}

void	numeric_argument_error(char **args, t_main *main)
{
	ft_putstr_fd("exit\nbash: exit: ", 2);
	ft_putstr_fd(args[1], 2);
	ft_putstr_fd(ERR_NUM_ARG, 2);
	exit_minishell(main, 2);
}
