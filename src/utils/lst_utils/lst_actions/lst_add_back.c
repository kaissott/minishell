#include "../../../../includes/minishell.h"

static t_exec	*lst_last(t_exec *lst_exec)
{
	if (lst_exec)
	{
		while (lst_exec)
		{
			if (lst_exec->next == NULL)
				return (lst_exec);
			lst_exec = lst_exec->next;
		}
	}
	return (NULL);
}

void	lst_add_back(t_exec **lst_exec, t_exec *new)
{
	t_exec	*last;

	if (lst_exec && new)
	{
		if (*lst_exec)
		{
			last = lst_last(*lst_exec);
			last->next = new;
		}
		else
			*lst_exec = new;
	}
}
