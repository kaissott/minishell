/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 10:50:39 by karamire          #+#    #+#             */
/*   Updated: 2024/11/20 13:25:00 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*index;
	t_list	*newelmt;
	void	*fcontent;

	if (!(f) || !lst || !del)
		return (NULL);
	index = NULL;
	while (lst != NULL)
	{
		fcontent = f(lst->content);
		newelmt = ft_lstnew(fcontent);
		if (!newelmt)
		{
			del(fcontent);
			ft_lstclear(&index, del);
			return (NULL);
		}
		ft_lstadd_back(&index, newelmt);
		lst = lst->next;
	}
	return (index);
}
