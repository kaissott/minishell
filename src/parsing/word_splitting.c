/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_splitting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 02:30:14 by ludebion          #+#    #+#             */
/*   Updated: 2025/07/22 21:39:33 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_parse_error	process_split_words(t_token_chunk *chunk,
		t_token **new_tokens, char **words)
{
	size_t			i;
	t_parse_error	errcode;

	i = 0;
	while (words[i])
	{
		if (*new_tokens && i == 0 && chunk->value[0] != ' '
			&& chunk->value[0] != '\n' && chunk->value[0] != '\t')
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

static t_parse_error	split_chunk_by_ifs(t_token_chunk *chunk,
		t_token **new_tokens)
{
	char			**words;
	t_parse_error	errcode;

	words = split_charset(chunk->value, " \n\t");
	if (!words)
		return (ERR_MALLOC);
	errcode = process_split_words(chunk, new_tokens, words);
	free_strs(words);
	return (errcode);
}

static t_parse_error	apply_word_splitting(t_token_chunk *chunk,
		t_token **new_tokens)
{
	t_parse_error	errcode;

	if (!chunk)
		return (ERR_NONE);
	if (chunk_contains_ifs_chars(chunk->value) && chunk->is_expanded
		&& chunk->type == T_STRING)
	{
		errcode = split_chunk_by_ifs(chunk, new_tokens);
		if (errcode != ERR_NONE)
			return (errcode);
	}
	else if (!*new_tokens)
	{
		errcode = create_first_token(new_tokens, chunk);
		if (errcode != ERR_NONE)
			return (errcode);
	}
	else
	{
		errcode = keep_chunk(token_lst_last(*new_tokens), chunk);
		if (errcode != ERR_NONE)
			return (errcode);
	}
	return (apply_word_splitting(chunk->next, new_tokens));
}

static t_parse_error	process_token(t_main *shell, t_token *token)
{
	t_token			*new_tokens;
	t_parse_error	errcode;

	new_tokens = NULL;
	if (token_contains_ifs_chunks(token))
	{
		errcode = apply_word_splitting(token->chunks, &new_tokens);
		if (errcode != ERR_NONE)
		{
			free_token_lst(&new_tokens);
			return (errcode);
		}
		replace_split_token(&shell->token, new_tokens, token);
	}
	else
	{
		errcode = cat_chunks(token);
		if (errcode != ERR_NONE)
		{
			free_token_lst(&new_tokens);
			return (errcode);
		}
	}
	return (ERR_NONE);
}

t_parse_error	word_splitting(t_main *shell)
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
		{
			shell->errcode = 12;
			return (errcode);
		}
		token = next;
	}
	return (ERR_NONE);
}
