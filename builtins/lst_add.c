/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 02:14:25 by kaissramire       #+#    #+#             */
/*   Updated: 2025/03/28 17:43:42 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

// void	lstadd_back(t_cmd **lst, t_cmd *new)
// {
// 	t_cmd	*last;

// 	if (new == NULL)
// 		return ;
// 	if ((*lst) == NULL)
// 	{
// 		*lst = new;
// 		return ;
// 	}
// 	last = *lst;
// 	while (last->next != NULL)
// 	{
// 		last = last->next;
// 	}
// 	last->next = new;
// 	return ;
// }

// t_cmd	*lstnew(char *content)
// {
// 	t_cmd	*newcontent;

// 	newcontent = malloc(sizeof(t_list));
// 	if (newcontent == NULL)
// 		return (NULL);
// 	newcontent->content = content;
// 	newcontent->next = NULL;
// 	return (newcontent);
// }
