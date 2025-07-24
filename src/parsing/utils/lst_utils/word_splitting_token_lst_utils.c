/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_splitting_token_lst_utils.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 21:02:34 by ludebion          #+#    #+#             */
/*   Updated: 2025/07/24 08:21:13 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_parse_error	create_first_token(t_token **new_tokens, t_token_chunk *chunk)
{
	t_token			*new_token;
	t_parse_error	errcode;

	new_token = ft_calloc(1, sizeof(t_token));
	if (!new_token)
		return (ERR_MALLOC);
	errcode = keep_chunk(new_token, chunk);
	if (errcode != ERR_NONE)
		return (errcode);
	token_lst_add_back(new_tokens, new_token);
	return (ERR_NONE);
}

t_parse_error	create_new_token_with_word(t_token **new_tokens, char *word)
{
	t_token			*new_token;
	t_parse_error	errcode;

	new_token = ft_calloc(1, sizeof(t_token));
	if (!new_token)
		return (ERR_MALLOC);
	errcode = create_and_add_splitted_chunk(&new_token->chunks, word);
	if (errcode != ERR_NONE)
	{
		free_token(new_token);
		return (errcode);
	}
	new_token->value = ft_strdup(new_token->chunks->value);
	if (!new_token->value)
	{
		free_token(new_token);
		return (errcode);
	}
	token_lst_add_back(new_tokens, new_token);
	return (ERR_NONE);
}
