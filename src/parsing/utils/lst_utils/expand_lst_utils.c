/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_lst_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 02:31:11 by ludebion          #+#    #+#             */
/*   Updated: 2025/07/19 02:31:11 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

t_expand	*create_expand(t_expand_type type, char *value)
{
	t_expand	*new_expand;

	if (!value)
		return (NULL);
	new_expand = ft_calloc(1, sizeof(t_expand));
	if (!new_expand)
	{
		free(value);
		return (NULL);
	}
	new_expand->type = type;
	new_expand->value = value;
	new_expand->next = NULL;
	return (new_expand);
}

void	expand_lst_add_back(t_expand **lst, t_expand *new)
{
	t_expand	*tmp;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return ;
}

void	expand_lst_delone(t_expand **expand_lst, t_expand *node_to_delete)
{
	t_expand	*tmp;

	if (!expand_lst || !*expand_lst || !node_to_delete)
		return ;
	if (*expand_lst == node_to_delete)
	{
		*expand_lst = node_to_delete->next;
		if (node_to_delete->value)
			free(node_to_delete->value);
		free(node_to_delete);
		return ;
	}
	tmp = *expand_lst;
	while (tmp && tmp->next != node_to_delete)
		tmp = tmp->next;
	if (tmp && tmp->next == node_to_delete)
	{
		tmp->next = node_to_delete->next;
		if (node_to_delete->value)
			free(node_to_delete->value);
		free(node_to_delete);
	}
}

void	print_expand_lst(t_expand *lst, char *msg)
{
	size_t	i;

	i = 1;
	printf("\n%s\n", msg);
	if (!lst)
	{
		printf("The expand list is empty\n");
		return ;
	}
	while (lst)
	{
		printf("Node [%zu] :\n", i++);
		if (lst->value)
			printf("\tvalue : %s\n", lst->value);
		else
			printf("\tNo value\n");
		printf("\ttype : %d\n", lst->type);
		lst = lst->next;
	}
}
