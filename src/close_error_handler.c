/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_error_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaissramirez <kaissramirez@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 01:10:44 by karamire          #+#    #+#             */
/*   Updated: 2025/07/17 02:15:06 by kaissramire      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit_error_minishell(t_main *main, int errcode, char *err)
{

	if (main)
	{
		free_struct(main);
		free(main);
	}
	ft_putendl_fd(err, 2);
	exit(errcode);
}
//ok

void	exit_error_two_close(t_main *main_struct, int fd1, int fd2)
{
	if (fd1 > 1)
	{
		if (close(fd1) == -1)
		{
			// if (fd2 > 1)
			// {
			// 	if (close(fd2) == -1)
			// 		exit_error_minishell(main_struct, errno,"Close failed");
			// 	fd2 = -1;
			// }
			exit_error_minishell(main_struct, errno, "Close failed");
		}
	}
	if (fd2 > 1)
	{
		if (close(fd2) == -1)
			exit_error_minishell(main_struct, errno, "Close failed");
		fd2 = -1;
	}
}
