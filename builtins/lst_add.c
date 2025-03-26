/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaissramirez <kaissramirez@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 02:14:25 by kaissramire       #+#    #+#             */
/*   Updated: 2025/03/26 02:14:43 by kaissramire      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	lstadd_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*last;

	if (new == NULL)
		return ;
	if ((*lst) == NULL)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next != NULL)
	{
		last = last->next;
	}
	last->next = new;
	return ;
}

t_cmd	*lstnew(char *content)
{
	t_cmd	*newcontent;

	newcontent = malloc(sizeof(t_list));
	if (newcontent == NULL)
		return (NULL);
	newcontent->content = content;
	newcontent->next = NULL;
	return (newcontent);
}
