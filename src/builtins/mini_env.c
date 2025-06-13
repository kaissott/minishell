/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 18:52:10 by karamire          #+#    #+#             */
/*   Updated: 2025/06/13 16:48:09 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


bool	env_print(t_main *main)
{
	t_env	*temp;

	temp = main->env;
	while (temp)
	{
		if (ft_putstr_fd(temp->env, STDOUT_FILENO) == -1)
			free_and_exit_error(main, ERR_WRITE, errno);
		if (write(STDOUT_FILENO, "\n", 1) == -1)
			free_and_exit_error(main, ERR_WRITE, errno);
		temp = temp->next;
	}
	return (true);
}
