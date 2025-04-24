/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:49:43 by karamire          #+#    #+#             */
/*   Updated: 2025/04/24 17:59:32 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	lstadd_backs(t_p **lst, t_p *new)
{
	t_p	*last;

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

t_p	*lstnews(char *content)
{
	t_p	*newcontent;

	newcontent = malloc(sizeof(t_p));
	if (newcontent == NULL)
		return (NULL);
	newcontent->arg = content;
	newcontent->next = NULL;
	return (newcontent);
}
int	main(void)
{
	t_p	*p;

	p = lstnews("echo");
	lstadd_backs(&p, lstnews("test"));
	printf("%s\n", p->arg);
	printf("%s\n", p->next->arg);
}
