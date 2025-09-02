/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_splitting_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 02:30:11 by ludebion          #+#    #+#             */
/*   Updated: 2025/09/02 03:48:49 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	chunk_contains_ifs_chars(t_shell *shell, char *str)
{
	size_t	i;
	size_t	j;
	char	*ifs_env;
	bool	var_found;

	var_found = false;
	ifs_env = get_var_value(shell, "IFS", &var_found);
	if (!var_found)
		ifs_env = " \n\t";
	i = 0;
	while (str[i])
	{
		j = 0;
		while (ifs_env[j])
		{
			if (str[i] == ifs_env[j])
			{
				if (var_found)
					free(ifs_env);
				return (true);
			}
			j++;
		}
		i++;
	}
	if (var_found)
		free(ifs_env);
	return (false);
}

bool	token_contains_ifs_chunks(t_shell *shell, t_token *token)
{
	t_token_chunk	*chunk;

	chunk = token->chunks;
	while (chunk)
	{
		if (chunk_contains_ifs_chars(shell, chunk->value) && chunk->is_expanded)
			return (true);
		chunk = chunk->next;
	}
	return (false);
}

t_parse_error	keep_chunk(t_token *token, t_token_chunk *chunk)
{
	t_parse_error	errcode;

	if (!chunk)
		return (ERR_NONE);
	errcode = create_and_add_splitted_chunk(&token->chunks, chunk->value);
	if (errcode != ERR_NONE)
		return (errcode);
	return (cat_chunks(token));
}

t_parse_error	handle_first_word(t_token **new_tokens, char *word)
{
	t_parse_error	errcode;

	errcode = create_and_add_splitted_chunk(&(*new_tokens)->chunks, word);
	if (errcode != ERR_NONE)
		return (errcode);
	return (cat_chunks(*new_tokens));
}

void	replace_split_token(t_token **tokens, t_token *new_tokens,
		t_token *token)
{
	t_token	*tmp;
	t_token	*prev;
	t_token	*last;

	tmp = *tokens;
	prev = NULL;
	while (tmp && tmp != token)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (!tmp)
		return ;
	last = new_tokens;
	while (last->next)
		last = last->next;
	last->next = tmp->next;
	if (!prev)
		*tokens = new_tokens;
	else
		prev->next = new_tokens;
	free_token(tmp);
}
