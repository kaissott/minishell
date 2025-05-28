/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_token_add_back.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luca <luca@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 19:55:34 by ludebion          #+#    #+#             */
/*   Updated: 2025/05/26 17:50:11 by luca             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	lst_token_add_back(t_token **lst, t_token *new)
{
	t_token	*last;

	if (lst && new)
	{
		if (*lst)
		{
			last = lst_token_last(*lst);
			last->next = new;
		}
		else
			*lst = new;
	}
}
