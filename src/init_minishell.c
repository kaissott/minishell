/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 23:20:44 by karamire          #+#    #+#             */
/*   Updated: 2025/07/23 02:03:25 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_main	*init_minishell(char **env)
{
	t_main	*main_struct;

	main_struct = ft_calloc(1, sizeof(t_main));
	if (!main_struct)
		exit_error_minishell(main_struct, errno, ERR_MEM);
	main_struct->env = NULL;
	check_env_available(env, main_struct);
	main_struct->std_out = dup(STDOUT_FILENO);
	main_struct->std_in = dup(STDIN_FILENO);
	main_struct->env_tab = NULL;
	if (main_struct->std_out == -1 || main_struct->std_in == -1)
	{
		exit_error_two_close(main_struct, main_struct->std_out,
			main_struct->std_in);
		exit_error_minishell(main_struct, errno, "Dup failed");
	}
	return (main_struct);
}
