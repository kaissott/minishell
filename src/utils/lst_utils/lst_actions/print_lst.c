#include "../../../../includes/minishell.h"

void	print_lst(t_lst_node *lst, char *msg)
{
	size_t	i;
	size_t	j;

	i = 1;
	j = 0;
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
			while (lst->cmd[j])
			{
				printf("cmd[%zu]: [%s]\n", j, lst->cmd[j]);
				j++;
			}
			j = 0;
		}
		printf("infile fd : [%d] type : [%d]\n", lst->infile.fd,
			lst->infile.type);
		printf("outfile fd : [%d] type : [%d]\n", lst->outfile.fd,
			lst->outfile.type);
		lst = lst->next;
	}
}
