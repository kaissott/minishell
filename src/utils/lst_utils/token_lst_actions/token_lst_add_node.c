#include "../../../../includes/minishell.h"

static bool	token_lst_add_back(t_token **lst, t_token *new)
{
	t_token	*tmp;

	if (!lst || !new)
		return (false);
	if (!*lst)
	{
		*lst = new;
		return (true);
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (true);
}

static bool	lst_token_chunk_add_back(t_token_chunk **lst, t_token_chunk *new)
{
	t_token_chunk	*tmp;

	if (!lst || !new)
		return (false);
	if (!*lst)
	{
		*lst = new;
		return (true);
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (true);
}

t_parse_error	create_and_add_word_chunk(t_token_chunk **lst_chunk,
		const char *cmd, const ssize_t len, char quote)
{
	t_token_chunk	*new_word_chunk;

	new_word_chunk = ft_calloc(1, sizeof(t_token_chunk));
	if (!new_word_chunk)
		return (ERR_MALLOC);
	if (quote == '\'')
		new_word_chunk->type = T_STRING;
	else
		new_word_chunk->type = T_ENV_STRING;
	new_word_chunk->value = ft_substr(cmd, 0, len);
	if (!new_word_chunk->value)
	{
		free(new_word_chunk);
		return (ERR_MALLOC);
	}
	if (!lst_token_chunk_add_back(lst_chunk, new_word_chunk))
	{
		free(new_word_chunk->value);
		free(new_word_chunk);
		return (ERR_MALLOC);
	}
	return (ERR_NONE);
}

t_parse_error	token_lst_add_node(t_token **token_lst, const char *cmd,
		const ssize_t len, t_token_type token_type)
{
	t_token	*new_token;

	new_token = ft_calloc(1, sizeof(t_token));
	if (!new_token)
		return (ERR_MALLOC);
	new_token->type = token_type;
	new_token->value = ft_substr(cmd, 0, len);
	if (!new_token->value)
		return (ERR_MALLOC);
	if (!token_lst_add_back(token_lst, new_token))
	{
		free(new_token->value);
		free(new_token);
		return (ERR_MALLOC);
	}
	return (ERR_NONE);
}

t_parse_error	token_lst_add_token_chunks(t_env **env_lst, t_token **token_lst,
		t_token *new_token)
{
	t_token_chunk	*tmp;
	char			*prev;

	tmp = new_token->chunks;
	new_token->type = T_WORD;
	if (expand_chunk(env_lst, new_token) == -1)
		return (-1);
	while (tmp)
	{
		prev = new_token->value;
		new_token->value = join_or_dup(prev, tmp->value);
		if (!new_token->value || !tmp->next)
			break ;
		tmp = tmp->next;
	}
	if (new_token->value && token_lst_add_back(token_lst, new_token))
		return (ERR_NONE);
	free_token_lst(&new_token);
	return (ERR_MALLOC);
}
