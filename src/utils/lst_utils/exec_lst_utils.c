#include "../../../includes/minishell.h"

t_exec	*create_exec_cmd(void)
{
	t_exec	*new_cmd;

	new_cmd = ft_calloc(1, sizeof(t_exec));
	if (!new_cmd)
		return (NULL);
	new_cmd->infile.fd = STDIN_FILENO;
	new_cmd->outfile.fd = STDOUT_FILENO;
	new_cmd->next = NULL;
	return (new_cmd);
}

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
	dprintf(2,"\n%s\n", msg);
	if (!lst)
	{
		dprintf(2,"The list is empty\n");
		return ;
	}
	while (lst)
	{
		dprintf(2,"Node [%zu]\n", i++);
		if (lst->cmd)
		{
			j = 0;
			while (lst->cmd[j])
			{
				dprintf(2,"\tcmd[%zu]: [%s]\n", j, lst->cmd[j]);
				j++;
			}
		}
		dprintf(2,"\tinfile fd : [%d] type : [%d]\n", lst->infile.fd,
			lst->infile.type);
		dprintf(2,"\toutfile fd : [%d] type : [%d]\n", lst->outfile.fd,
			lst->outfile.type);
		lst = lst->next;
	}
}
