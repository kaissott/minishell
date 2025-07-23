/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:50:09 by karamire          #+#    #+#             */
/*   Updated: 2025/07/23 18:03:32 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void	error_exit(char *str, int exitnbr, int fd)
{
	if (fd > 0)
		close(fd);
	ft_putendl_fd(str, 2);
	exit(exitnbr);
}
