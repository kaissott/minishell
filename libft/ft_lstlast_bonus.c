/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luca <luca@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 19:52:50 by ludebion          #+#    #+#             */
/*   Updated: 2025/02/28 04:08:22 by luca             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_lst	*ft_lstlast(t_lst *lst)
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
// int	main(void)
// {
// 	t_lst *lst;
// 	t_lst *last;

// 	lst = ft_lstnew("Hello");
// 	lst->next = ft_lstnew("world");
// 	last = ft_lstlast(lst);
// 	printf("Dernier élément : %s\n", (char *)last->content);
// }
