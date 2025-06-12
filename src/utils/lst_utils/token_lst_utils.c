#include "../../../includes/minishell.h"

static void	free_token(t_token *node)
{
	t_token_chunk	*next;

	if (!node)
		return ;
	if (node->value)
		free(node->value);
	while (node->chunks)
	{
		next = node->chunks->next;
		if (node->chunks->value)
			free(node->chunks->value);
		free(node->chunks);
		node->chunks = next;
	}
	free(node);
}

void	token_lst_delone(t_token **lst, t_token *node_to_delete)
{
	t_token	*tmp;

	if (!lst || !*lst || !node_to_delete)
		return ;
	if (*lst == node_to_delete)
	{
		*lst = node_to_delete->next;
		free_token(node_to_delete);
		return ;
	}
	tmp = *lst;
	while (tmp)
	{
		if (tmp->next == node_to_delete)
		{
			tmp->next = node_to_delete->next;
			free_token(node_to_delete);
			return ;
		}
		tmp = tmp->next;
	}
}

void	print_token_lst(t_token *lst, char *msg)
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
		if (lst->chunks)
		{
			while (lst->chunks)
			{
				printf("\tchunk value: [%s] type : [%d]\n", lst->chunks->value,
					lst->chunks->type);
				lst->chunks = lst->chunks->next;
			}
		}
		lst = lst->next;
	}
}
