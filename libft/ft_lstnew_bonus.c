/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luca <luca@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 19:27:51 by ludebion          #+#    #+#             */
/*   Updated: 2025/02/28 04:08:22 by luca             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_lst	*ft_lstnew(void *content)
{
	t_lst	*new_elem;

	new_elem = ft_calloc(1, sizeof(t_lst));
	if (!new_elem)
		return (NULL);
	new_elem->content = content;
	new_elem->next = NULL;
	return (new_elem);
}

// int	main(void)
// {
// 	t_lst *lst;

// 	lst = ft_lstnew("Hello");
// 	printf("Nouvel élément : %s\n", (char *)lst->content);
// }
