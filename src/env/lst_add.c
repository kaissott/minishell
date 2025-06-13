/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 02:14:25 by kaissramire       #+#    #+#             */
/*   Updated: 2025/06/13 16:49:21 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	new->next = NULL;
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
