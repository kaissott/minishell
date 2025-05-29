#include "../../../../includes/minishell.h"

void	lst_add_back(t_lst_node **lst, t_lst_node *new)
{
	t_lst_node	*last;

	if (lst && new)
	{
		if (*lst)
		{
			last = lst_last(*lst);
			last->next = new;
		}
		else
			*lst = new;
	}
}
