#include "../../../../includes/minishell.h"

static t_exec	*lst_last(t_exec *exec_lst)
{
	if (exec_lst)
	{
		while (exec_lst)
		{
			if (exec_lst->next == NULL)
				return (exec_lst);
			exec_lst = exec_lst->next;
		}
	}
	return (NULL);
}

void	lst_add_back(t_exec **exec_lst, t_exec *new)
{
	t_exec	*last;

	if (exec_lst && new)
	{
		if (*exec_lst)
		{
			last = lst_last(*exec_lst);
			last->next = new;
		}
		else
			*exec_lst = new;
	}
}
