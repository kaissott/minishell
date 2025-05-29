#include "../../../../includes/minishell.h"

void	lst_token_add_front(t_token **lst, t_token *new)
{
	if (lst && new)
	{
		if (*lst)
			new->next = *lst;
		*lst = new;
	}
}
