/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luca <luca@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 20:23:13 by ludebion          #+#    #+#             */
/*   Updated: 2025/03/07 16:08:48 by luca             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_lst *lst, void (*del)(void *))
{
	if (!del && lst)
	{
		free(lst);
		lst = NULL;
		return ;
	}
	if (lst)
	{
		del(lst->content);
		free(lst);
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

// 	lst = NULL;
// 	*lst = ft_lstnew("Hello");
// 	(*lst)->next = ft_lstnew("world");
// 	printf("Liste avant suppression : \n\n");
// 	while (*lst)
// 	{
// 		printf("Mon élément : %s\n", (char *)(*lst)->content);
// 		*lst = (*lst)->next;
// 	}
// 	printf("\nListe après suppression : \n\n");
// 	ft_lstdelone(*lst, del);
// 	while (*lst)
// 	{
// 		printf("Mon élément : %s\n", (char *)(*lst)->content);
// 		*lst = (*lst)->next;
// 	}
// }

// int	main(void)
// {
// 	t_lst	*lst;

// 	lst = ft_lstnew("Hello");
// 	lst->next = ft_lstnew("world");
// 	printf("Liste avant suppression : \n\n");
// 	while (lst)
// 	{
// 		printf("Mon élément : %s\n", (char *)lst->content);
// 		lst = lst->next;
// 	}
// 	printf("\nListe après suppression : \n\n");
// 	ft_lstdelone(lst, del);
// 	while (lst)
// 	{
// 		printf("Mon élément : %s\n", (char *)lst->content);
// 		lst = lst->next;
// 	}
// }
