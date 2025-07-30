/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_error_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaissramirez <kaissramirez@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 01:10:44 by karamire          #+#    #+#             */
/*   Updated: 2025/07/30 18:54:43 by kaissramire      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_error_minishell(t_shell *main, int errcode, char *err)
{
	if (main)
	{
		ft_safe_close(&main->std_in, main);
		ft_safe_close(&main->std_out, main);
		close_node(main);
		free_struct(main);
		if (main)
			free(main);
	}
	ft_putendl_fd(err, 2);
	exit(errcode);
}

void	exit_error_two_close(t_shell *main, int *fd1, int *fd2)
{
	if (*fd1 > 1)
	{
		ft_safe_close(fd1, main);
	}
	if (*fd2 > 1)
	{
		ft_safe_close(fd2, main);
	}
}
