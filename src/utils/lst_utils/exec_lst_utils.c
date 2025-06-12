#include "../../../includes/minishell.h"

void	exec_lst_add_back(t_exec **lst, t_exec *new)
{
	t_exec	*tmp;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return ;
}

void	exec_lst_delone(t_exec *lst, t_exec *node_to_delete)
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

void	print_exec_lst(t_exec *lst, char *msg)
{
	size_t	i;
	size_t	j;

	i = 1;
	printf("\n%s\n", msg);
	if (!lst)
	{
		printf("The list is empty\n");
		return ;
	}
	while (lst)
	{
		printf("Node [%zu]\n", i++);
		if (lst->cmd)
		{
			j = 0;
			while (lst->cmd[j])
			{
				printf("\tcmd[%zu]: [%s]\n", j, lst->cmd[j]);
				j++;
			}
		}
		printf("\tinfile fd : [%d] type : [%d]\n", lst->infile.fd,
			lst->infile.type);
		printf("\toutfile fd : [%d] type : [%d]\n", lst->outfile.fd,
			lst->outfile.type);
		lst = lst->next;
	}
}
