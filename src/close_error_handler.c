/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_error_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 01:10:44 by karamire          #+#    #+#             */
/*   Updated: 2025/07/24 00:16:41 by karamire         ###   ########.fr       */
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

void	exit_error_two_close(t_shell *main, int fd1, int fd2)
{
	if (fd1 > 1)
		close(fd1);
	if (fd2 > 1)
		close(fd2);
}
