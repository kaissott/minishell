#include "../../includes/minishell.h"

static t_parse_error	replace_chunk_value(t_env **env_lst,
		t_expand **expand_lst, t_token_chunk *chunk)
{
	t_expand	*tmp;
	char		*prev;
	char		*var_value;

	tmp = *expand_lst;
	while (tmp)
	{
		prev = chunk->value;
		if (tmp->type == T_EXPAND_VAR)
			var_value = get_var_value(env_lst, tmp->value);
		else
			var_value = tmp->value;
		if (var_value)
			chunk->value = join_or_dup(prev, var_value);
		if (tmp->type == T_EXPAND_VAR)
			free(var_value);
		if (!chunk->value)
			return (ERR_MALLOC);
		tmp = tmp->next;
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
	if (!new_expand || !lst_expand_add_back(expand_lst, new_expand))
		return (ERR_MALLOC);
	return (i);
}

static ssize_t	handle_var(t_expand **expand_lst, char *var)
{
	ssize_t		i;
	t_expand	*new_expand;

	i = 1;
	if (!var[i])
	{
		new_expand = create_expand(T_EXPAND_VAR, ft_substr(var, 0, 1));
		if (!new_expand || !lst_expand_add_back(expand_lst, new_expand))
			return (ERR_MALLOC);
		return (1);
	}
	if (var[i] == '$' || var[i] == '?')
		new_expand = create_expand(T_EXPAND_VAR, ft_substr(var, 0, 2));
	else
	{
		while (var[i] && (ft_isalnum(var[i]) || var[i] == '_'))
			i++;
		if (i == 1)
			new_expand = create_expand(T_EXPAND_VAR, ft_substr(var, 0, i));
		else
			new_expand = create_expand(T_EXPAND_VAR, ft_substr(var, 1, i - 1));
	}
	if (!new_expand || !lst_expand_add_back(expand_lst, new_expand))
		return (ERR_MALLOC);
	if (i == 1)
	{
		if (var[i] == '$' || var[i] == '?')
			return (2);
		if (!ft_isalnum(var[i]))
			return (1);
	}
	return (i);
}

static t_parse_error	handle_chunk_value(t_env **env_lst,
		t_expand **expand_lst, t_token_chunk *chunk)
{
	size_t	i;
	ssize_t	len;

	i = 0;
	while (chunk->value[i])
	{
		if (chunk->value[i] == '$')
			len = handle_var(expand_lst, &chunk->value[i]);
		else
			len = handle_word(expand_lst, &chunk->value[i]);
		if (len <= 0)
			return (ERR_EXPAND);
		i += len;
	}
	free(chunk->value);
	chunk->value = NULL;
	replace_chunk_value(env_lst, expand_lst, chunk);
	return (ERR_NONE);
}

t_parse_error	expand_chunk(t_env **env_lst, t_token *new_token)
{
	t_token_chunk	*tmp;
	t_expand		*expand_lst;

	tmp = new_token->chunks;
	while (tmp)
	{
		expand_lst = NULL;
		if (tmp->type == T_ENV_STRING && ft_strchr(tmp->value, '$'))
			handle_chunk_value(env_lst, &expand_lst, tmp);
		free_expand_lst(&expand_lst);
		tmp = tmp->next;
	}
	return (ERR_NONE);
}
