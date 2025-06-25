/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 18:52:10 by karamire          #+#    #+#             */
/*   Updated: 2025/06/25 19:56:05 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	env_print(t_main *main, char **cmd)
{
	t_env	*temp;

	temp = main->env;
	if(cmd[1])
	{
		if (ft_putstr_fd("env: ", 2) == -1)
			free_and_exit_error(main, NULL, ERR_WRITE, errno);
		if (ft_putstr_fd("'", 2) == -1)
			free_and_exit_error(main, NULL, ERR_WRITE, errno);
		if (ft_putstr_fd(cmd[1], 2) == -1)
			free_and_exit_error(main, NULL, ERR_WRITE, errno);
		if (ft_putstr_fd("': ", 2) == -1)
			free_and_exit_error(main, NULL, ERR_WRITE, errno);
		if (ft_putstr_fd("No such file or directory", 2) == -1)
			free_and_exit_error(main, NULL, ERR_WRITE, errno);
		main->errcode = 127;
		return(true);
	}
	while (temp)
	{
		if (ft_putstr_fd(temp->env, STDOUT_FILENO) == -1)
			free_and_exit_error(main, NULL, ERR_WRITE, errno);
		if (write(STDOUT_FILENO, "\n", 1) == -1)
			free_and_exit_error(main, NULL, ERR_WRITE, errno);
		temp = temp->next;
	}
	return (true);
}
