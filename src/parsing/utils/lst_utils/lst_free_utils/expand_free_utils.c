/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_free_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 02:30:30 by ludebion          #+#    #+#             */
/*   Updated: 2025/07/23 00:25:41 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_expand_lst(t_expand **expand_lst)
{
	t_expand	*current;
	t_expand	*next;

	if (!expand_lst || !*expand_lst)
		return ;
	current = *expand_lst;
	while (current)
	{
		next = current->next;
		if (current->value)
			free(current->value);
		free(current);
		current = next;
	}
	*expand_lst = NULL;
}
