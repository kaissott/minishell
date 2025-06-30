#include "../../includes/minishell.h"

void	replace_split_token(t_token **tokens, t_token *new_tokens,
		t_token *token)
{
	t_token	*tmp;
	t_token	*prev;
	t_token	*last;

	tmp = *tokens;
	prev = NULL;
	while (tmp && tmp != token)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (!tmp)
		return ;
	last = new_tokens;
	while (last->next)
		last = last->next;
	last->next = tmp->next;
	if (!prev)
		*tokens = new_tokens;
	else
		prev->next = new_tokens;
	// free_token(tmp);
}

t_parse_error	split_chunk(t_token *new_token, t_token_chunk *chunk,
		t_token **new_tokens)
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
			errcode = create_and_add_chunk_words_splitting(&(*new_tokens)->chunks,
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
			errcode = create_and_add_chunk_words_splitting(&new_token->chunks,
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

t_parse_error	keep_chunk(t_token *new_token, t_token_chunk *chunk)
{
	t_parse_error	errcode;

	if (!chunk)
		return (ERR_NONE);
	errcode = create_and_add_chunk_words_splitting(&new_token->chunks,
			chunk->value);
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
		errcode = split_chunk(new_token, chunk, new_tokens);
		if (errcode != ERR_NONE)
			return (errcode);
	}
	else
	{
		if (!*new_tokens)
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
	}
	return (apply_word_splitting(token, new_token, new_tokens, chunk->next));
}

t_parse_error	split_by_ifs(t_main *shell)
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
		errcode = cat_chunks(token);
		if (errcode != ERR_NONE)
			return (errcode);
		token = next_token;
	}
	return (ERR_NONE);
}

static ssize_t	handle_word(t_expand **expand_lst, char *word)
{
	ssize_t		i;
	t_expand	*new_expand;

	i = 0;
	while (word[i] && word[i] != '$')
		i++;
	new_expand = create_expand(T_EXPAND_WORD, ft_substr(word, 0, i));
	if (!new_expand)
		return (ERR_MALLOC);
	expand_lst_add_back(expand_lst, new_expand);
	return (i);
}

static t_expand	*extract_expand_var(char *var, ssize_t *i)
{
	if (var[*i] == '$' || var[*i] == '?' || var[*i] == '/')
		return (create_expand(T_EXPAND_VAR, ft_substr(var, 0, 2)));
	while (var[*i] && (ft_isalnum(var[*i]) || var[*i] == '_'))
		(*i)++;
	return (create_expand(T_EXPAND_VAR, ft_substr(var, 1, *i - 1)));
}

static ssize_t	handle_var(t_expand **expand_lst, char *var,
		t_token_chunk *chunk)
{
	ssize_t		i;
	t_expand	*new_expand;

	(void)chunk;
	i = 1;
	if (!var[i] || var[i] == ' ' || var[i] == '\t' || var[i] == '\n')
	{
		if (chunk->next)
			return (i);
		new_expand = create_expand(T_EXPAND_VAR, ft_strdup("$"));
		if (!new_expand)
			return (ERR_MALLOC);
		expand_lst_add_back(expand_lst, new_expand);
		return (i);
	}
	new_expand = extract_expand_var(var, &i);
	if (!new_expand)
		return (ERR_MALLOC);
	expand_lst_add_back(expand_lst, new_expand);
	if (i == 1 && (var[i] == '$' || var[i] == '?' || var[i] == '/'))
		return (2);
	return (i);
}

static t_token_chunk	*handle_chunk_value(t_main *shell,
		t_expand **expand_lst, t_token *token, t_token_chunk *chunk)
{
	size_t			i;
	ssize_t			len;
	t_token_chunk	*next;

	i = 0;
	next = chunk->next;
	while (chunk->value[i])
	{
		if (chunk->value[i] == '$')
			len = handle_var(expand_lst, &chunk->value[i], chunk);
		else
			len = handle_word(expand_lst, &chunk->value[i]);
		if (len == 1 && chunk->value[i] == '$' && chunk->type != T_DOUBLE_QUOTED
			&& next && (next->type == T_SINGLE_QUOTED
				|| next->type == T_DOUBLE_QUOTED))
		{
			remove_char_at(chunk->value, i);
			continue ;
		}
		if (len <= 0)
			return (NULL);
		i += len;
	}
	if (*expand_lst != NULL)
	{
		chunk->is_expanded = true;
		replace_chunk_value(shell, expand_lst, token, chunk);
	}
	if (!chunk)
		return (next->next);
	return (next);
}

t_parse_error	expansion(t_main *shell)
{
	t_parse_error	errcode;
	t_token			*token;
	t_token			*next;
	t_token_chunk	*chunk;
	t_expand		*expand_lst;

	token = shell->token;
	while (token)
	{
		next = token->next;
		chunk = token->chunks;
		while (chunk)
		{
			expand_lst = NULL;
			if ((chunk->type == T_STRING || chunk->type == T_DOUBLE_QUOTED)
				&& ft_strchr(chunk->value, '$') && !token->is_delimiter)
			{
				chunk = handle_chunk_value(shell, &expand_lst, token, chunk);
				free_expand_lst(&expand_lst);
				if (!chunk && expand_lst)
					return (ERR_MALLOC);
			}
			else
				chunk = chunk->next;
		}
		token = next;
	}
	if (shell->token)
	{
		errcode = split_by_ifs(shell);
		if (errcode != ERR_NONE)
			return (errcode);
	}
	return (ERR_NONE);
}
