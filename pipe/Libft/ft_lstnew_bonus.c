/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 04:40:15 by karamire          #+#    #+#             */
/*   Updated: 2024/11/17 04:45:05 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*newcontent;

	newcontent = malloc(sizeof(t_list));
	if (newcontent == NULL)
		return (NULL);
	newcontent->content = content;
	newcontent->next = NULL;
	return (newcontent);
}
