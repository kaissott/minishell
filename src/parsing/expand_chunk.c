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
	if (!var[i])
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
	if (i == 1 && (var[i] == '$' || var[i] == '?'))
		return (2);
	return (i);
}

static t_parse_error	handle_chunk_value(t_main *shell, t_expand **expand_lst,
		t_token_chunk *chunk)
{
	size_t	i;
	ssize_t	len;

	i = 0;
	while (chunk->value[i])
	{
		if (chunk->value[i] == '$')
			len = handle_var(expand_lst, &chunk->value[i], chunk);
		else
			len = handle_word(expand_lst, &chunk->value[i]);
		if (len <= 0)
			return (len);
		i += len;
	}
	free(chunk->value);
	chunk->value = NULL;
	if (*expand_lst != NULL)
		replace_chunk_value(shell, expand_lst, chunk);
	return (ERR_NONE);
}

t_parse_error	expand_chunk(t_main *shell, t_token *new_token)
{
	int				errcode;
	t_token_chunk	*tmp;
	t_expand		*expand_lst;

	tmp = new_token->chunks;
	while (tmp)
	{
		expand_lst = NULL;
		if (tmp->type == T_ENV_STRING && ft_strchr(tmp->value, '$'))
		{
			errcode = handle_chunk_value(shell, &expand_lst, tmp);
			free_expand_lst(&expand_lst);
			if (errcode != ERR_NONE)
				return (errcode);
		}
		tmp = tmp->next;
	}
	return (ERR_NONE);
}
