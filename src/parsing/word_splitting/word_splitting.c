/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_splitting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 02:30:14 by ludebion          #+#    #+#             */
/*   Updated: 2025/09/02 03:51:11 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_parse_error	process_split_words(t_shell *shell,
		t_token_chunk *chunk, t_token **new_tokens, char **words)
{
	size_t			i;
	t_parse_error	errcode;

	i = 0;
	while (words[i])
	{
		if (*new_tokens && i == 0 && begin_or_end_by_ifs(shell, chunk->value,
				true))
		{
			errcode = handle_first_word(new_tokens, words[i]);
			if (errcode != ERR_NONE)
				return (errcode);
		}
		else
		{
			errcode = create_new_token_with_word(new_tokens, words[i]);
			if (errcode != ERR_NONE)
				return (errcode);
		}
		i++;
	}
	return (ERR_NONE);
}

static t_parse_error	split_chunk_by_ifs(t_shell *shell, t_token_chunk *chunk,
		t_token **new_tokens)
{
	char			**words;
	t_parse_error	errcode;
	char			*ifs_env;
	bool			var_found;

	var_found = false;
	ifs_env = get_var_value(shell, "IFS", &var_found);
	if (var_found)
		words = split_charset(chunk->value, ifs_env);
	else
		words = split_charset(chunk->value, DEFAULT_IFS);
	if (var_found)
		free(ifs_env);
	if (!words)
		return (ERR_MALLOC);
	errcode = process_split_words(shell, chunk, new_tokens, words);
	free_strs(words);
	return (errcode);
}

static t_parse_error	apply_word_splitting(t_shell *shell,
		t_token_chunk *chunk, t_token **new_tokens, bool prev_sep)
{
	t_parse_error	errcode;

	if (!chunk)
		return (ERR_NONE);
	if (chunk_contains_ifs_chars(shell, chunk->value) && chunk->is_expanded
		&& chunk->type == T_STRING)
	{
		errcode = split_chunk_by_ifs(shell, chunk, new_tokens);
		if (chunk_contains_ifs_chars(shell, chunk->value
				+ ft_strlen(chunk->value) - 1))
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
	return (apply_word_splitting(shell, chunk->next, new_tokens, prev_sep));
}

static t_parse_error	process_token(t_shell *shell, t_token *token)
{
	t_token			*new_tokens;
	t_parse_error	errcode;

	new_tokens = NULL;
	if (token_contains_ifs_chunks(shell, token) && !token->is_redir)
	{
		errcode = apply_word_splitting(shell, token->chunks, &new_tokens,
				false);
		if (errcode != ERR_NONE)
			return (errcode);
		replace_split_token(&shell->token, new_tokens, token);
	}
	else
	{
		if (!token->is_blank && (!token_contains_ifs_chunks(shell, token)
				|| !token->is_redir))
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
	t_token			*token;
	t_token			*next;
	t_parse_error	errcode;

	token = shell->token;
	while (token)
	{
		next = token->next;
		errcode = process_token(shell, token);
		if (errcode != ERR_NONE)
			return (errcode);
		token = next;
	}
	return (ERR_NONE);
}
