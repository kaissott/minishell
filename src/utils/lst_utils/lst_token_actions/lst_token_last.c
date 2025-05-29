#include "../../../../includes/minishell.h"

t_token	*lst_token_last(t_token *lst)
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
