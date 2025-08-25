/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 17:38:27 by karamire          #+#    #+#             */
/*   Updated: 2025/08/25 19:04:47 by karamire         ###   ########.fr       */
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

void	exit_minishell(t_shell *main, int exitcode)
{
	if (main->env_tab)
		free(main->env_tab);
	close_node(main);
	free_struct(main);
	ft_safe_close(&main->std_in, main);
	ft_safe_close(&main->std_out, main);
	free(main);
	rl_clear_history();
	exit(exitcode);
}

void	numeric_argument_error(char **args, t_shell *main)
{
	ft_putstr_fd("exit\nminishell: exit: ", 2);
	ft_putstr_fd(args[1], 2);
	ft_putstr_fd(ERR_NUM_ARG, 2);
	exit_minishell(main, 2);
}
