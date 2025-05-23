/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_last.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luca <luca@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 19:52:50 by ludebion          #+#    #+#             */
/*   Updated: 2025/05/20 01:29:09 by luca             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*lst_last(t_token *lst)
{
	if (lst)
	{
		while (lst)
		{
			if (lst->next == NULL)
				return (lst);
			lst = lst->next;
		}
	}
	return (NULL);
}
