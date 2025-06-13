/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luca <luca@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 20:27:38 by ludebion          #+#    #+#             */
/*   Updated: 2025/03/07 16:05:20 by luca             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_lst **lst, void (*del)(void *))
{
	t_lst	*next;

	if (lst && *lst)
	{
		while (*lst)
		{
			next = (*lst)->next;
			ft_lstdelone(*lst, del);
			*lst = next;
		}
		lst = NULL;
	}
}

// void	del(void *content)
// {
// 	free(content);
// }

// int	main(void)
// {
// 	t_lst	**lst;
// 	t_lst	*lst_first;
// 	int		count;

// 	lst = ft_calloc(1, sizeof(t_lst));
// 	*lst = ft_lstnew(ft_strdup("Hello"));
// 	(*lst)->next = ft_lstnew(ft_strdup("world"));
// 	lst_first = *lst;
// 	count = 0;
// 	printf("Liste avant clear : \n\n");
// 	while (*lst)
// 	{
// 		printf("Mon élément n [%d] : %s\n", count, (char *)(*lst)->content);
// 		*lst = (*lst)->next;
// 	}
// 	printf("\nListe après clear : \n\n");
// 	ft_lstclear(lst, del);
// 	while (*lst)
// 	{
// 		printf("Mon élément n [%d] : %s\n", count, (char *)(*lst)->content);
// 		*lst = (*lst)->next;
// 	}
// }
