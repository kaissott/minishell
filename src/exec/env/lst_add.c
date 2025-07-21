/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 17:41:01 by karamire          #+#    #+#             */
/*   Updated: 2025/07/21 17:41:01 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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

t_env	*lstnew(char *content, t_main *main)
{
	t_env	*newcontent;

	newcontent = malloc(sizeof(t_env));
	if (newcontent == NULL)
		free_and_exit_error(main, content, ERR_MEM, 12);
	newcontent->env = content;
	newcontent->next = NULL;
	return (newcontent);
}
