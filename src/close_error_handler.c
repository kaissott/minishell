/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_error_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 01:10:44 by karamire          #+#    #+#             */
/*   Updated: 2025/06/16 01:47:26 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


void	exit_error_minishell(t_main *main, int errcode, char *err)
{
	if (main)
	{
		exit_error_two_close(main, main->std_in, main->std_out);
		free_struct(main);
		free(main);
	}
	perror(err);
	exit(errcode);
}

void	exit_error_one_close(t_main *main_struct, int fd1)
{
	if (fd1 > 1)
	{
		if (close(fd1) == -1)
		{
			exit_error_minishell(main_struct, errno,"Close failed");
		}
	}
}
void	exit_error_two_close(t_main *main_struct, int fd1, int fd2)
{
	if (fd1 > 1)
	{
		if (close(fd1) == -1)
		{
			if (fd2 > 1)
			{
				if (close(fd2) == -1)
					exit_error_minishell(main_struct, errno,"Close failed");
			}
			exit_error_minishell(main_struct, errno,"Close failed");
		}
	}
	if (fd2 > 1)
	{
		if (close(fd2) == -1)
			exit_error_minishell(main_struct, errno,"Close failed");
	}
}
