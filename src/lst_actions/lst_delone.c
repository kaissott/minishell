/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_delone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luca <luca@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:12:13 by luca              #+#    #+#             */
/*   Updated: 2025/05/20 01:29:01 by luca             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	lst_delone(t_token *lst, t_token *node_to_delete)
{
	t_token	*new_next_node;

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
