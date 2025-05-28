/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_add_back.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luca <luca@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 19:55:34 by ludebion          #+#    #+#             */
/*   Updated: 2025/05/26 17:44:29 by luca             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	lst_add_back(t_lst_node **lst, t_lst_node *new)
{
	t_lst_node	*last;

	if (lst && new)
	{
		if (*lst)
		{
			last = lst_last(*lst);
			last->next = new;
		}
		else
			*lst = new;
	}
}
