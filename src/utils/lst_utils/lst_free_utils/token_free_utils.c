#include "../../../../includes/minishell.h"

void	print_chunk_lst(t_token_chunk *lst, char *msg)
{
	size_t	i;

	i = 1;
	printf("\n%s\n", msg);
	if (!lst)
	{
		printf("The chunk list is empty\n");
		return ;
	}
	while (lst)
	{
		printf("Node [%zu] :\n", i++);
		if (lst->value)
			printf("\tvalue : %s\n", lst->value);
		else
			printf("\tNo chunk value\n");
		printf("\ttype : %d\n", lst->type);
		lst = lst->next;
	}
}

static void	free_chunk_lst(t_token_chunk **chunk)
{
	t_token_chunk	*current;
	t_token_chunk	*next;

	current = *chunk;
	while (current)
	{
		next = current->next;
		if (current->value)
			free(current->value);
		free(current);
		current = next;
	}
}

void	free_token(t_token *token)
{
	if (!token)
		return ;
	free_chunk_lst(&token->chunks);
	if (token->value)
		free(token->value);
	free(token);
}

void	free_token_lst(t_token **token_lst)
{
	t_token	*current;
	t_token	*next;

	if (!token_lst || !*token_lst)
		return ;
	current = *token_lst;
	while (current)
	{
		next = current->next;
		free_token(current);
		current = next;
	}
	*token_lst = NULL;
}
