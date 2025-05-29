#include "../../../../includes/minishell.h"

void	lst_token_add_back(t_token **lst, t_token *new)
{
	t_token	*last;

	if (lst && new)
	{
		if (*lst)
		{
			last = lst_token_last(*lst);
			last->next = new;
		}
		else
			*lst = new;
	}
}
