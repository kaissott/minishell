#include "../../includes/minishell.h"

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
	return (ERR_NONE);
}
