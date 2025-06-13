#include "../../../../includes/minishell.h"

void	free_chunk_lst(t_token_chunk *chunk)
{
	t_token_chunk	*tmp;

	while (chunk)
	{
		tmp = chunk->next;
		if (chunk->value)
			free(chunk->value);
		free(chunk);
		chunk = tmp;
	}
}

void	free_token(t_token *token)
{
	if (!token)
		return ;
	free_chunk_lst(token->chunks);
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
