/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 02:31:24 by ludebion          #+#    #+#             */
/*   Updated: 2025/08/27 02:00:00 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_or_dup(char *prev, char *next)
{
	char	*new_val;

	if (prev && next)
		new_val = ft_strjoin(prev, next);
	else if (prev)
		new_val = ft_strdup(prev);
	else if (next)
		new_val = ft_strdup(next);
	else
		new_val = ft_strdup("");
	free(prev);
	return (new_val);
}

bool	is_dollar_alone(t_token_chunk *chunk, size_t i, size_t len,
		t_token_chunk *next)
{
	if (len == 1 && chunk->value[i] == '$' && chunk->type != T_DOUBLE_QUOTED
		&& next && (next->type == T_SINGLE_QUOTED
			|| next->type == T_DOUBLE_QUOTED))
	{
		while (chunk->value[i])
		{
			chunk->value[i] = chunk->value[i + 1];
			i++;
		}
		return (true);
	}
	return (false);
}
