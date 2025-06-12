#include "../../../includes/minishell.h"

static void	chunk_lst_add_back(t_token_chunk **chunk_lst, t_token_chunk *new)
{
	t_token_chunk	*tmp;

	if (!chunk_lst || !new)
		return ;
	if (!*chunk_lst)
	{
		*chunk_lst = new;
		return ;
	}
	tmp = *chunk_lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return ;
}

t_parse_error	create_and_add_chunk(t_token_chunk **chunk_lst, char *cmd,
		ssize_t len, char quote)
{
	t_token_chunk	*new_chunk;

	new_chunk = ft_calloc(1, sizeof(t_token_chunk));
	if (!new_chunk)
		return (ERR_MALLOC);
	if (quote == '\'')
		new_chunk->type = T_STRING;
	else
		new_chunk->type = T_ENV_STRING;
	new_chunk->value = ft_substr(cmd, 0, len);
	if (!new_chunk->value)
	{
		free_chunk_lst(new_chunk);
		return (ERR_MALLOC);
	}
	chunk_lst_add_back(chunk_lst, new_chunk);
	return (ERR_NONE);
}

t_parse_error	token_lst_add_chunks(t_env **env_lst, t_token **token_lst,
		t_token *new_token)
{
	t_token_chunk	*tmp;
	char			*prev;

	tmp = new_token->chunks;
	new_token->type = T_WORD;
	if (expand_chunk(env_lst, new_token) != ERR_NONE)
	{
		free_token(new_token);
		return (ERR_EXPAND);
	}
	while (tmp)
	{
		prev = new_token->value;
		new_token->value = join_or_dup(prev, tmp->value);
		if (!new_token->value || !tmp->next)
			break ;
		tmp = tmp->next;
	}
	if (!new_token->value)
	{
		free_token(new_token);
		return (ERR_MALLOC);
	}
	token_lst_add_back(token_lst, new_token);
	return (ERR_NONE);
}
