/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luca <luca@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 03:58:05 by ludebion          #+#    #+#             */
/*   Updated: 2025/02/28 04:08:22 by luca             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_lst	*ft_lstmap(t_lst *lst, void *(*f)(void *), void (*del)(void *))
{
	t_lst	*new_lst;
	t_lst	*new_elem;
	void	*new_elem_content;

	if (!lst || !f || !del)
		return (NULL);
	new_lst = NULL;
	while (lst != NULL)
	{
		new_elem_content = f(lst->content);
		new_elem = ft_lstnew(new_elem_content);
		if (!new_elem)
		{
			del(new_elem_content);
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		ft_lstadd_back(&new_lst, new_elem);
		lst = lst->next;
	}
	return (new_lst);
}

// void	*f(void *content)
// {
// 	char	*str;

// 	str = (char *)(content);
// 	return (ft_memcpy(ft_strdup(str), "Hey", 5));
// }
// void	del(void *content)
// {
// 	free(content);
// }

// int	main(void)
// {
// 	t_lst	*lst;
// 	t_lst	*new_lst;
// 	t_lst	*lst_first;
// 	int		count;

// 	lst = ft_calloc(1, sizeof(t_lst));
// 	lst = ft_lstnew("Hello");
// 	lst->next = ft_lstnew("world");
// 	lst_first = lst;
// 	count = 0;
// 	printf("Liste avant map : \n\n");
// 	while (lst)
// 	{
// 		printf("Mon élément n [%d] : %s\n", count, (char *)lst->content);
// 		count++;
// 		lst = lst->next;
// 	}
// 	lst = lst_first;
// 	printf("\nListe après map : \n\n");
// 	new_lst = ft_lstmap(lst, f, del);
// 	count = 0;
// 	while (new_lst)
// 	{
// 		printf("Mon élément n [%d] : %s\n", count, (char *)new_lst->content);
// 		count++;
// 		new_lst = new_lst->next;
// 	}
// }
