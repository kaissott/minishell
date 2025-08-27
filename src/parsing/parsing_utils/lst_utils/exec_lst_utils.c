/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_lst_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 02:31:07 by ludebion          #+#    #+#             */
/*   Updated: 2025/08/26 05:40:05 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_exec	*create_exec_cmd(void)
{
	t_exec	*new_cmd;

	new_cmd = ft_calloc(1, sizeof(t_exec));
	if (!new_cmd)
		return (NULL);
	new_cmd->infile.fd = STDIN_FILENO;
	new_cmd->outfile.fd = STDOUT_FILENO;
	new_cmd->next = NULL;
	return (new_cmd);
}

void	exec_lst_add_back(t_exec **lst, t_exec *new)
{
	t_exec	*tmp;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return ;
}

void	exec_lst_delone(t_exec *lst, t_exec *node_to_delete)
{
	t_exec	*new_next_node;

	if (lst && node_to_delete)
	{
		new_next_node = node_to_delete->next;
		while (lst)
		{
			if (lst->next == node_to_delete)
			{
				free(lst->next);
				lst->next = new_next_node;
				return ;
			}
			lst = lst->next;
		}
	}
}
