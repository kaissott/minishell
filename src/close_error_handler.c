/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_error_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 01:10:44 by karamire          #+#    #+#             */
/*   Updated: 2025/07/23 10:04:02 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_error_minishell(t_shell *main, int errcode, char *err)
{
	if (main)
	{
		close(main->std_in);
		close(main->std_out);
		close_node(main);
		free_struct(main);
		if (main)
			free(main);
	}
	ft_putendl_fd(err, 2);
	exit(errcode);
}

void	exit_error_two_close(t_shell *main_struct, int fd1, int fd2)
{
	if (fd1 > 1)
	{
		if (close(fd1) == -1)
			exit_error_minishell(main_struct, errno, "Close failed");
	}
	if (fd2 > 1)
	{
		if (close(fd2) == -1)
			exit_error_minishell(main_struct, errno, "Close failed");
		fd2 = -1;
	}
}
