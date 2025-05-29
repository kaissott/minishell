#include "../../../../includes/minishell.h"

size_t	lst_size(t_lst_node *lst)
{
	size_t	size;

	size = 0;
	if (lst)
	{
		while (lst)
		{
			size++;
			lst = lst->next;
		}
	}
	return (size);
}
