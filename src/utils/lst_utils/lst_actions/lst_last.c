#include "../../../../includes/minishell.h"

t_lst_node	*lst_last(t_lst_node *lst)
{
	if (lst)
	{
		while (lst)
		{
			if (lst->next == NULL)
				return (lst);
			lst = lst->next;
		}
	}
	return (NULL);
}
