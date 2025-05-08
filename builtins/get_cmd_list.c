/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaissramirez <kaissramirez@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:49:43 by karamire          #+#    #+#             */
/*   Updated: 2025/05/08 21:32:46 by kaissramire      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

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
// int	main(void)
// {
// 	t_p	*p;

// 	p = lstnews("echo");
// 	lstadd_backs(&p, lstnews("test"));
// 	printf("%s\n", p->arg);
// 	printf("%s\n", p->next->arg);
// }
