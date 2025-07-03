/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:45:05 by karamire          #+#    #+#             */
/*   Updated: 2025/07/03 21:43:22 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"


void	safe_close(int fd, t_main *main)
{
	t_exec	*tmp;

	tmp = main->exec;
	while (tmp && fd != tmp->outfile.fd && fd != tmp->infile.fd)
	{
		tmp = tmp->next;
	}
	if (tmp == NULL && fd > 1)
		close(fd);
	return ;
}




void	wait_child(pid_t last, t_main *main)
{
	int	status;

	while (waitpid(last, &status, 0) > 0)
	{
		if (WIFEXITED(status) && WEXITSTATUS(status) == 127)
			main->errcode = 127;
		if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
			main->errcode = 1;
	}
	while (wait(NULL) > 0)
		;
}

