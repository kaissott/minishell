#include "../../includes/minishell.h"

static t_parse_error	apply_word_splitting(t_token **new_tokens,
		t_token_chunk *chunk)
{
	size_t			i;
	char			**words;
	t_token			*new_token;
	t_token_chunk	*new_chunk;

	i = 0;
	words = ft_split(chunk->value, ' ');
	if (!words)
		return (ERR_MALLOC);
	while (words[i])
	{
		new_token = ft_calloc(1, sizeof(t_token));
		if (!new_token)
			return (ERR_MALLOC);
		new_token->value = ft_strdup(words[i]);
		if (!new_token->value)
			return (ERR_MALLOC);
		new_chunk = ft_calloc(1, sizeof(t_token_chunk));
		new_chunk->value = ft_strdup(words[i]);
		free(words[i]);
		if (!new_chunk->value)
			return (ERR_MALLOC);
		new_chunk->type = T_STRING;
		new_chunk->is_expanded = true;
		new_token->chunks = new_chunk;
		token_lst_add_back(new_tokens, new_token);
		i++;
	}
	free(words);
	return (ERR_NONE);
}

t_parse_error	split_by_ifs(t_main *shell)
{
	bool			splitted;
	t_token			*token;
	t_token			*prev;
	t_token			*last;
	t_token			*to_free;
	t_token			*new_tokens;
	t_token_chunk	*chunk;
	t_parse_error	errcode;

	prev = NULL;
	token = shell->token;
	while (token)
	{
		new_tokens = NULL;
		splitted = false;
		chunk = token->chunks;
		while (chunk)
		{
			if (chunk->is_expanded && chunk->type == T_STRING
				&& contains_ifs_chars(chunk->value))
			{
				errcode = apply_word_splitting(&new_tokens, chunk);
				if (errcode != ERR_NONE)
					return (errcode);
				last = token_lst_last(new_tokens);
				if (prev)
					prev->next = new_tokens;
				else
					shell->token = new_tokens;
				last->next = token->next;
				prev = last;
				to_free = token;
				token = last->next;
				free_token(to_free);
				splitted = true;
				break ;
			}
			chunk = chunk->next;
		}
		if (!splitted)
		{
			errcode = cat_chunks(token);
			if (errcode != ERR_NONE)
				return (errcode);
			prev = token;
			token = token->next;
		}
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
	if (var[*i] == '$' || var[*i] == '?')
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

	i = 1;
	if (!var[i] || var[i] == ' ' || var[i] == '\t' || var[i] == '\n')
	{
		// if (chunk->next)
		// 	return (i);
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
	if (i == 1 && (var[i] == '$' || var[i] == '?'))
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
		if (len == 1 && i == 0 && chunk->type != T_DOUBLE_QUOTED && chunk->next
			&& (chunk->next->type == T_SINGLE_QUOTED
				|| chunk->next->type == T_DOUBLE_QUOTED))
		{
			chunk_lst_delone(&token->chunks, chunk);
			return (next);
		}
		if (len <= 0)
			return (NULL);
		i += len;
	}
	// print_expand_lst(*expand_lst,
	// 	"EXPAND LIST BEFORE REPLACE CHUNK VALUE : \n");
	if (*expand_lst != NULL)
	{
		chunk->is_expanded = true;
		replace_chunk_value(shell, expand_lst, token, chunk);
	}
	return (chunk->next);
}

t_parse_error	expansion(t_main *shell)
{
	t_parse_error	errcode;
	t_token			*token;
	t_token_chunk	*chunk;
	t_expand		*expand_lst;

	token = shell->token;
	while (token)
	{
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
		token = token->next;
	}
	errcode = split_by_ifs(shell);
	if (errcode != ERR_NONE)
		return (errcode);
	return (ERR_NONE);
}
