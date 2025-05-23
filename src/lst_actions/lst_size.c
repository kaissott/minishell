/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_size.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luca <luca@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 19:49:56 by ludebion          #+#    #+#             */
/*   Updated: 2025/05/20 01:29:16 by luca             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	lst_size(t_token *lst)
{
	size_t	size;

	size = 0;
	if (lst)
	{
		while (lst)
		{
			size++;
			lst = lst->next;
		}
	}
	return (size);
}
