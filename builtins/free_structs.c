/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 21:09:40 by karamire          #+#    #+#             */
/*   Updated: 2025/06/03 22:33:17 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"

void	free_env(t_main *main)
{
	t_env	*head;
	t_env	*temp;

	head = main->mainenv;
	while (head->next != NULL)
	{
		temp = head->next;
		free(head->env);
		free(head);
		head = temp;
	}
	free(head->env);
	free(head);
}

void	free_node(t_main *main)
{
	t_lst_node	*temp;
	t_lst_node	*next;
	int			i;

	i = 0;
	temp = main->node;
	while (temp != NULL)
	{
		next = temp->next;
		if (temp->cmd)
		{
			while (temp->cmd[i])
				free(temp->cmd[i++]);
			free(temp->cmd);
		}
		free(temp);
		temp = next;
		i = 0;
	}
	main->node = NULL;
}

int	free_struct(t_main *main)
{
	if (main->mainenv != NULL)
		free_env(main);
	if (main->node != NULL)
		free_node(main);
	free(main);
}
