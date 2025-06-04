#include "../../../../includes/minishell.h"

void	lst_delone(t_exec *lst, t_exec *node_to_delete)
{
	t_exec	*new_next_node;

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
