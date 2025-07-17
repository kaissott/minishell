#include "../../includes/minishell.h"

static t_parse_error	split_chunk_by_ifs(t_token *new_token,
		t_token_chunk *chunk, t_token **new_tokens)
{
	size_t			i;
	char			**words;
	t_parse_error	errcode;

	i = 0;
	words = split_charset(chunk->value, " \n\t");
	if (!words)
		return (ERR_MALLOC);
	while (words[i])
	{
		if (*new_tokens && i == 0 && chunk->value[0] != ' ')
		{
			errcode = create_and_add_splitted_chunk(&(*new_tokens)->chunks,
					words[i]);
			if (errcode != ERR_NONE)
			{
				free_strs(words);
				return (errcode);
			}
			errcode = cat_chunks(*new_tokens);
			if (errcode != ERR_NONE)
			{
				free_strs(words);
				return (errcode);
			}
		}
		else
		{
			new_token = ft_calloc(1, sizeof(t_token));
			if (!new_token)
			{
				free_strs(words);
				return (ERR_MALLOC);
			}
			errcode = create_and_add_splitted_chunk(&new_token->chunks,
					words[i]);
			if (errcode != ERR_NONE)
			{
				free_token(new_token);
				free_strs(words);
				return (errcode);
			}
			errcode = cat_chunks(new_token);
			if (errcode != ERR_NONE)
			{
				free_token(new_token);
				free_strs(words);
				return (errcode);
			}
			token_lst_add_back(new_tokens, new_token);
		}
		i++;
	}
	free_strs(words);
	return (ERR_NONE);
}

static t_parse_error	keep_chunk(t_token *new_token, t_token_chunk *chunk)
{
	t_parse_error	errcode;

	if (!chunk)
		return (ERR_NONE);
	errcode = create_and_add_splitted_chunk(&new_token->chunks, chunk->value);
	if (errcode != ERR_NONE)
	{
		free_token(new_token);
		return (errcode);
	}
	errcode = cat_chunks(new_token);
	if (errcode != ERR_NONE)
	{
		free_token(new_token);
		return (errcode);
	}
	return (ERR_NONE);
}

static t_parse_error	apply_word_splitting(t_token *token, t_token *new_token,
		t_token **new_tokens, t_token_chunk *chunk)
{
	t_parse_error	errcode;

	if (!chunk && new_tokens)
		return (ERR_NONE);
	if (contains_ifs_chars(chunk->value) && chunk->is_expanded
		&& chunk->type == T_STRING)
	{
		errcode = split_chunk_by_ifs(new_token, chunk, new_tokens);
		if (errcode != ERR_NONE)
			return (errcode);
	}
	else if (!*new_tokens)
	{
		new_token = ft_calloc(1, sizeof(t_token));
		if (!new_token)
			return (ERR_MALLOC);
		errcode = keep_chunk(new_token, chunk);
		if (errcode != ERR_NONE)
			return (errcode);
		token_lst_add_back(new_tokens, new_token);
	}
	else
	{
		errcode = keep_chunk(token_lst_last(*new_tokens), chunk);
		if (errcode != ERR_NONE)
			return (errcode);
	}
	return (apply_word_splitting(token, new_token, new_tokens, chunk->next));
}

t_parse_error	word_splitting(t_main *shell)
{
	bool			contain_ifs_chunks;
	t_token			*token;
	t_token			*new_tokens;
	t_token			*new_token;
	t_token_chunk	*chunk;
	t_token			*next_token;
	t_parse_error	errcode;

	token = shell->token;
	while (token)
	{
		new_token = NULL;
		new_tokens = NULL;
		chunk = token->chunks;
		contain_ifs_chunks = false;
		next_token = token->next;
		while (chunk)
		{
			if (contains_ifs_chars(chunk->value) && chunk->is_expanded)
				contain_ifs_chunks = true;
			chunk = chunk->next;
		}
		if (contain_ifs_chunks)
		{
			errcode = apply_word_splitting(token, new_token, &new_tokens,
					token->chunks);
			if (errcode != ERR_NONE)
				return (errcode);
			replace_split_token(&shell->token, new_tokens, token);
		}
		else
		{
			if (token)
			{
				errcode = cat_chunks(token);
				if (errcode != ERR_NONE)
					return (errcode);
			}
		}
		token = next_token;
	}
	return (ERR_NONE);
}
