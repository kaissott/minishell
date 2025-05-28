/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_token_delone.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luca <luca@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:12:13 by luca              #+#    #+#             */
/*   Updated: 2025/05/27 18:50:04 by luca             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	free_token(t_token *node)
{
	if (!node)
		return ;
	if (node->value)
		free(node->value);
	free(node);
}

void	lst_token_delone(t_token **lst, t_token *node_to_delete)
{
	t_token	*tmp;

	if (!lst || !*lst || !node_to_delete)
		return ;
	if (*lst == node_to_delete)
	{
		*lst = node_to_delete->next;
		free_token(node_to_delete);
		return ;
	}
	tmp = *lst;
	while (tmp)
	{
		if (tmp->next == node_to_delete)
		{
			tmp->next = node_to_delete->next;
			free_token(node_to_delete);
			return ;
		}
		tmp = tmp->next;
	}
}
