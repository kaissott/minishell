/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luca <luca@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 20:41:03 by ludebion          #+#    #+#             */
/*   Updated: 2025/02/28 04:08:22 by luca             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_lst *lst, void (*f)(void *))
{
	if (lst && f)
	{
		while (lst)
		{
			f(lst->content);
			lst = lst->next;
		}
	}
}

// void	f(void *content)
// {
// 	char	*str;

// 	str = (char *)(content);
// 	ft_memcpy(str, "Hey", 5);
// }

// int	main(void)
// {
// 	t_lst	*lst;
// 	t_lst	*lst_first;
// 	int		count;

// 	lst = ft_calloc(1, sizeof(t_lst));
// 	lst = ft_lstnew(ft_strdup("Hello"));
// 	lst_first = lst;
// 	lst->next = ft_lstnew(ft_strdup("world"));
// 	count = 0;
// 	printf("Liste avant modif : \n\n");
// 	while (lst)
// 	{
// 		printf("Mon élément n [%d] : %s\n", count, (char *)lst->content);
// 		count++;
// 		lst = lst->next;
// 	}
// 	lst = lst_first;
// 	printf("\nListe après modif : \n\n");
// 	ft_lstiter(lst, f);
// 	count = 0;
// 	while (lst)
// 	{
// 		printf("Mon élément n [%d] : %s\n", count, (char *)lst->content);
// 		count++;
// 		lst = lst->next;
// 	}
// }
