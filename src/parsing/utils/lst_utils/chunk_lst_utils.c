#include "../../../../includes/minishell.h"

t_token_chunk	*chunk_lst_last(t_token_chunk *lst)
{
	if (!lst)
		return (NULL);
	while (lst)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

void	chunk_lst_delone(t_token_chunk **chunk_lst,
		t_token_chunk *node_to_delete)
{
	t_token_chunk	*tmp;

	if (!chunk_lst || !*chunk_lst || !node_to_delete)
		return ;
	if (*chunk_lst == node_to_delete)
	{
		*chunk_lst = node_to_delete->next;
		if (node_to_delete->value)
			free(node_to_delete->value);
		free(node_to_delete);
		return ;
	}
	tmp = *chunk_lst;
	while (tmp && tmp->next != node_to_delete)
		tmp = tmp->next;
	if (tmp && tmp->next == node_to_delete)
	{
		tmp->next = node_to_delete->next;
		if (node_to_delete->value)
			free(node_to_delete->value);
		free(node_to_delete);
	}
}

void	chunk_lst_add_back(t_token_chunk **chunk_lst, t_token_chunk *new)
{
	t_token_chunk	*tmp;

	if (!chunk_lst || !new)
		return ;
	if (!*chunk_lst)
		*chunk_lst = new;
	else
	{
		tmp = *chunk_lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

t_parse_error	create_and_add_chunk(t_token_chunk **chunk_lst, char *cmd,
		ssize_t len, char quote)
{
	t_token_chunk	*new_chunk;

	new_chunk = ft_calloc(1, sizeof(t_token_chunk));
	if (!new_chunk)
		return (ERR_MALLOC);
	if (quote == '\'')
		new_chunk->type = T_SINGLE_QUOTED;
	else if (quote == '"')
		new_chunk->type = T_DOUBLE_QUOTED;
	else
		new_chunk->type = T_STRING;
	new_chunk->value = ft_substr(cmd, 0, len);
	if (!new_chunk->value)
	{
		free(new_chunk);
		return (ERR_MALLOC);
	}
	chunk_lst_add_back(chunk_lst, new_chunk);
	return (ERR_NONE);
}

t_parse_error	create_and_add_chunk_words_splitting(t_token_chunk **chunk_lst,
		char *value)
{
	t_token_chunk	*new_chunk;

	new_chunk = ft_calloc(1, sizeof(t_token_chunk));
	if (!new_chunk)
		return (ERR_MALLOC);
	new_chunk->type = T_STRING;
	new_chunk->value = ft_strdup(value);
	if (!new_chunk->value)
		return (ERR_MALLOC);
	chunk_lst_add_back(chunk_lst, new_chunk);
	return (ERR_NONE);
}

t_parse_error	cat_chunks(t_token *token)
{
	t_token_chunk	*chunk;
	char			*prev;

	prev = NULL;
	chunk = token->chunks;
	if (token->type == T_WORD)
		free(token->value);
	while (chunk)
	{
		token->value = join_or_dup(prev, chunk->value);
		if (!token->value)
		{
			free_token(token);
			return (ERR_MALLOC);
		}
		prev = token->value;
		chunk = chunk->next;
	}
	return (ERR_NONE);
}
