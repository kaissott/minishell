/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:42:20 by kaissramire       #+#    #+#             */
/*   Updated: 2025/06/02 17:52:02 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"

void	free_env_list(t_env *head)
{
	t_env	*tmp;

	while (head->next != NULL)
	{
		tmp = head->next;
		free(head->env);
		free(head);
		head = tmp;
	}
	free(head->env);
	free(head);
}
