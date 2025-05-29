#include "../../../../includes/minishell.h"

void	lst_add_front(t_lst_node **lst, t_lst_node *new)
{
	if (lst && new)
	{
		if (*lst)
			new->next = *lst;
		*lst = new;
	}
}
