/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luca <luca@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 19:55:34 by ludebion          #+#    #+#             */
/*   Updated: 2025/02/28 04:08:22 by luca             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_lst **lst, t_lst *new)
{
	t_lst	*last;

	if (lst && new)
	{
		if (*lst)
		{
			last = ft_lstlast(*lst);
			last->next = new;
		}
		else
			*lst = new;
	}
}

// int	main(void)
// {
// 	t_lst	**lst;
// 	t_lst	*lst_first;
// 	int		count;

// 	lst = ft_calloc(1, sizeof(t_lst));
// 	*lst = ft_lstnew("Hello");
// 	(*lst)->next = ft_lstnew("world");
// 	lst_first = *lst;
// 	count = 0;
// 	printf("Liste avant ajout à la fin : \n\n");
// 	while (*lst)
// 	{
// 		printf("Mon élément n [%d] : %s\n", count, (char *)(*lst)->content);
// 		*lst = (*lst)->next;
// 	}
// 	lst = &lst_first;
// 	printf("\nListe après ajout à la fin : \n\n");
// 	ft_lstadd_back(lst, ft_lstnew("this is Luca"));
// 	while (*lst)
// 	{
// 		printf("Mon élément n [%d] : %s\n", count, (char *)(*lst)->content);
// 		*lst = (*lst)->next;
// 	}
// }
