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

static bool	lst_word_part_add_back(t_word_part **lst, t_word_part *new)
{
	t_word_part	*tmp;

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

t_parse_error	create_and_add_word_part(t_word_part **lst_part,
		const char *cmd, const ssize_t len, char quote)
{
	t_word_part	*new_word_part;

	new_word_part = ft_calloc(1, sizeof(t_word_part));
	if (!new_word_part)
		return (ERR_MALLOC);
	if (quote == '\'')
		new_word_part->type = T_STRING;
	else
		new_word_part->type = T_ENV_STRING;
	new_word_part->value = ft_substr(cmd, 0, len);
	if (!new_word_part->value)
	{
		free(new_word_part);
		return (ERR_MALLOC);
	}
	if (!lst_word_part_add_back(lst_part, new_word_part))
	{
		free(new_word_part->value);
		free(new_word_part);
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

t_parse_error	token_lst_add_token_parts(t_token **token_lst,
		t_token *token_node)
{
	t_word_part	*tmp;
	char		*prev;

	tmp = token_node->parts;
	token_node->type = T_WORD;
	while (tmp)
	{
		prev = token_node->value;
		if (prev)
			token_node->value = ft_strjoin(prev, tmp->value);
		else
			token_node->value = ft_strdup(tmp->value);
		free(prev);
		if (!token_node->value || !tmp->next)
			break ;
		tmp = tmp->next;
	}
	if (token_node->value && token_lst_add_back(token_lst, token_node))
		return (ERR_NONE);
	free_token_lst(&token_node);
	return (ERR_MALLOC);
}
