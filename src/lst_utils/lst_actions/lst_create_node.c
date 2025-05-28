/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_create_node.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luca <luca@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 02:51:09 by luca              #+#    #+#             */
/*   Updated: 2025/05/26 17:51:34 by luca             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_lst_node	*lst_create_node(void)
{
	t_lst_node	*new_node;

	new_node = ft_calloc(1, sizeof(t_lst_node));
	if (!new_node)
		return (NULL);
	// new_node->value = ft_strdup(value);
	// if (!new_node->value)
	// {
	// 	free(new_node);
	// 	return (NULL);
	// }
	// new_node->type = type;
	return (new_node);
}
