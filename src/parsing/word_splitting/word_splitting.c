/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_splitting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 02:30:14 by ludebion          #+#    #+#             */
/*   Updated: 2025/09/02 22:58:31 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_parse_error	process_split_words(t_token_chunk *chunk,
		t_token **new_tokens, char **words, char *ifs_env)
{
	size_t			i;
	t_parse_error	errcode;

	i = 0;
	while (words[i])
	{
		if (*new_tokens && i == 0 && !begin_or_end_by_ifs(ifs_env, chunk->value,
				true))
			errcode = handle_first_word(new_tokens, words[i]);
		else
			errcode = create_new_token_with_word(new_tokens, words[i]);
		if (errcode != ERR_NONE)
			return (errcode);
		i++;
	}
	return (ERR_NONE);
}

static t_parse_error	split_chunk_by_ifs(t_token_chunk *chunk,
		t_token **new_tokens, char *ifs_env)
{
	char			**words;
	t_parse_error	errcode;
	bool			is_empty;

	errcode = ERR_NONE;
	is_empty = false;
	words = split_charset(chunk->value, ifs_env, &is_empty);
	if (!words)
	{
		if (!is_empty)
			return (ERR_MALLOC);
		chunk->is_blank = true;
	}
	if (!chunk->is_blank)
		errcode = process_split_words(chunk, new_tokens, words, ifs_env);
	free_strs(words);
	return (errcode);
}

static t_parse_error	apply_word_splitting(t_token_chunk *chunk,
		t_token **new_tokens, char *ifs_env, bool prev_sep)
{
	t_parse_error	errcode;

	if (!chunk)
		return (ERR_NONE);
	if (chunk_contains_ifs_chars(ifs_env, chunk->value) && chunk->is_expanded
		&& chunk->type == T_STRING)
	{
		errcode = split_chunk_by_ifs(chunk, new_tokens, ifs_env);
		if (begin_or_end_by_ifs(ifs_env, chunk->value, false))
			prev_sep = true;
	}
	else if (!*new_tokens)
		errcode = create_first_token(new_tokens, chunk);
	else
	{
		if (!prev_sep)
			errcode = keep_chunk(token_lst_last(*new_tokens), chunk);
		else
			errcode = create_new_token_with_word(new_tokens, chunk->value);
	}
	if (errcode != ERR_NONE)
		return (errcode);
	return (apply_word_splitting(chunk->next, new_tokens, ifs_env, prev_sep));
}

static t_parse_error	process_token(t_shell *shell, t_token *token,
		char *ifs_env)
{
	t_token			*new_tokens;
	t_parse_error	errcode;

	new_tokens = NULL;
	if (token_contains_ifs_chunks(ifs_env, token) && !token->is_redir)
	{
		errcode = apply_word_splitting(token->chunks, &new_tokens, ifs_env,
				false);
		if (errcode != ERR_NONE)
			return (errcode);
		replace_split_token(&shell->token, new_tokens, token);
	}
	else
	{
		if (!token->is_blank)
		{
			errcode = cat_chunks(token);
			if (errcode != ERR_NONE)
				return (errcode);
		}
	}
	return (ERR_NONE);
}

t_parse_error	word_splitting(t_shell *shell)
{
	char			*ifs_env;
	bool			var_found;
	t_token			*token;
	t_token			*next;
	t_parse_error	errcode;

	ifs_env = get_var_value(shell, "IFS", &var_found);
	token = shell->token;
	while (token)
	{
		next = token->next;
		errcode = process_token(shell, token, ifs_env);
		if (errcode != ERR_NONE)
		{
			if (var_found)
				free(ifs_env);
			return (errcode);
		}
		token = next;
	}
	if (var_found)
		free(ifs_env);
	return (ERR_NONE);
}
