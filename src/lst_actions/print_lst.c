#include "../../includes/minishell.h"

void	print_lst(t_token *lst, char *msg)
{
	size_t	i;

	i = 1;
	printf("\n%s\n", msg);
	if (!lst)
	{
		printf("The list is empty\n");
		return ;
	}
	while (lst)
	{
		printf("Node [%zu] ", i++);
		if (lst->value)
			printf("value: [%s] ", lst->value);
		else
			printf("value: [NULL] ");
		printf("type: [%d]\n", lst->type);
		lst = lst->next;
	}
}
