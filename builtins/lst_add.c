/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaissramirez <kaissramirez@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 02:14:25 by kaissramire       #+#    #+#             */
/*   Updated: 2025/05/20 19:25:23 by kaissramire      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"

void	lstadd_back(t_env **lst, t_env *new)
{
	t_env	*last;

	if (new == NULL)
		return ;
	if ((*lst) == NULL)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next != NULL)
		last = last->next;
	last->next = new;
	return ;
}

t_env	*lstnew(char *content)
{
	t_env	*newcontent;

	newcontent = malloc(sizeof(t_env));
	if (newcontent == NULL)
		return (NULL);
	newcontent->env = content;
	newcontent->next = NULL;
	return (newcontent);
}
