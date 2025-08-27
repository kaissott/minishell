/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_free_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 02:30:22 by ludebion          #+#    #+#             */
/*   Updated: 2025/08/26 05:40:50 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_exec(t_exec *exec)
{
	size_t	i;

	if (!exec)
		return ;
	if (exec->cmd)
	{
		i = 0;
		while (exec->cmd[i])
		{
			free(exec->cmd[i]);
			i++;
		}
		free(exec->cmd);
	}
	secure_close(&exec->infile.fd, STDIN_FILENO);
	secure_close(&exec->outfile.fd, STDOUT_FILENO);
	free(exec);
	exec = NULL;
}

void	free_exec_lst(t_exec **exec_lst)
{
	t_exec	*current;
	t_exec	*next;

	if (!exec_lst || !*exec_lst)
		return ;
	current = *exec_lst;
	while (current)
	{
		next = current->next;
		free_exec(current);
		current = next;
	}
	*exec_lst = NULL;
}
