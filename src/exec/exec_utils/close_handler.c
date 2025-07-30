/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaissramirez <kaissramirez@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 08:46:28 by kaissramire       #+#    #+#             */
/*   Updated: 2025/07/30 16:44:31 by kaissramire      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_a_file(int fd, t_shell *shell)
{
	t_exec	*tmp;

	tmp = shell->exec;
	while (tmp)
	{
		if (fd == tmp->infile.fd || fd == tmp->outfile.fd)
			return (true);
		tmp = tmp->next;
	}
	return (false);
}

void	ft_safe_close(int *fd, t_shell *main)
{
	if (*fd > 1 && is_a_file(*fd, main) == false)
	{
		if (close(*fd) == -1)
			perror("Close error");
		else
			*fd = -1;
	}
}

void	ft_safe_close_node(t_exec *tmp)
{
	if (tmp->infile.fd > 1)
	{
		if (close(tmp->infile.fd) == -1)
			perror("Close error");
		else
			tmp->infile.fd = -1;
	}
	if (tmp->outfile.fd > 1)
	{
		if (close(tmp->outfile.fd) == -1)
			perror("Close error");
		else
			tmp->outfile.fd = -1;
		tmp = tmp->next;
	}
}
