/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 02:29:20 by ludebion          #+#    #+#             */
/*   Updated: 2025/07/23 00:36:20 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static ssize_t	handle_var(t_expand **expand_lst, char *var,
		t_token_chunk *chunk)
{
	ssize_t		i;
	t_expand	*new_expand;

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

static t_parse_error	handle_chunk_value(t_main *shell, t_expand **expand_lst,
		t_token *token, t_token_chunk *chunk)
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
		if (len <= 0)
			return (ERR_MALLOC);
		if (is_dollar_alone(chunk, i, len, chunk->next))
			continue ;
		i += len;
	}
	return (replace_chunk_value(shell, expand_lst, token, chunk));
}

static t_parse_error	process_chunk(t_main *shell, t_token *token,
		t_token_chunk *chunk)
{
	t_expand		*expand_lst;
	t_token_chunk	*next;
	t_parse_error	errcode;

	while (chunk)
	{
		expand_lst = NULL;
		next = chunk->next;
		if ((chunk->type == T_STRING || chunk->type == T_DOUBLE_QUOTED)
			&& ft_strchr(chunk->value, '$') && !token->is_delimiter)
		{
			errcode = handle_chunk_value(shell, &expand_lst, token, chunk);
			free_expand_lst(&expand_lst);
			if (errcode != ERR_NONE)
				return (errcode);
		}
		chunk = next;
	}
	return (ERR_NONE);
}

t_parse_error	expansion(t_main *shell)
{
	t_token			*token;
	t_token			*next;
	t_token_chunk	*chunk;
	t_parse_error	errcode;

	token = shell->token;
	while (token)
	{
		next = token->next;
		chunk = token->chunks;
		errcode = process_chunk(shell, token, chunk);
		if (errcode != ERR_NONE)
			return (errcode);
		if (token)
			token = next;
		else
			token = next->next;
	}
	return (ERR_NONE);
}
