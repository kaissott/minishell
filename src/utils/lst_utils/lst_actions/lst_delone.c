#include "../../../../includes/minishell.h"

void	lst_delone(t_lst_node *lst, t_lst_node *node_to_delete)
{
	t_lst_node	*new_next_node;

	if (lst && node_to_delete)
	{
		new_next_node = node_to_delete->next;
		while (lst)
		{
			if (lst->next == node_to_delete)
			{
				free(lst->next);
				lst->next = new_next_node;
				return ;
			}
			lst = lst->next;
		}
	}
}
