/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 10:35:42 by karamire          #+#    #+#             */
/*   Updated: 2024/11/20 13:37:49 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*next;

	next = lst;
	if (lst == NULL || f == NULL)
		return ;
	while (next != NULL)
	{
		next = lst->next;
		f(lst->content);
		lst = next;
	}
}
