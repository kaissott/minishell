/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 08:46:28 by karamire          #+#    #+#             */
/*   Updated: 2025/07/30 21:37:18 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_a_file(int *fd, t_shell *shell)
{
	t_exec	*tmp;

	tmp = shell->exec;
	while (tmp)
	{
		if (*fd == tmp->infile.fd || *fd == tmp->outfile.fd)
			return (true);
		tmp = tmp->next;
	}
	return (false);
}

void	ft_safe_close(int *fd, t_shell *main)
{
	if (*fd > 1 && is_a_file(fd, main) == false)
	{
		if (close(*fd) == -1)
			perror("Close error");
		else
			*fd = -1;
	}
}

void	ft_safe_close_node(t_exec *tmp, int *fd1, int *fd2)
{
	if (*fd1 > 1)
	{
		if (close(*fd1) == -1)
			perror("Close error");
		else
			*fd1 = -1;
	}
	if (*fd2 > 1)
	{
		if (close(*fd2) == -1)
			perror("Close error");
		else
			*fd2 = -1;
		tmp = tmp->next;
	}
}
