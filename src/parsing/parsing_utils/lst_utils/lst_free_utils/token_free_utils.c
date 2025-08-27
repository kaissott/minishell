/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_free_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 02:30:38 by ludebion          #+#    #+#             */
/*   Updated: 2025/07/26 05:49:24 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_chunk_lst(t_token_chunk **chunk)
{
	t_token_chunk	*current;
	t_token_chunk	*next;

	current = *chunk;
	while (current)
	{
		next = current->next;
		if (current->value)
			free(current->value);
		free(current);
		current = next;
	}
}

void	free_token(t_token *token)
{
	if (!token)
		return ;
	free_chunk_lst(&token->chunks);
	if (token->value)
		free(token->value);
	free(token);
	token = NULL;
}

void	free_token_lst(t_token **token_lst)
{
	t_token	*current;
	t_token	*next;

	if (!token_lst || !*token_lst)
		return ;
	current = *token_lst;
	while (current)
	{
		next = current->next;
		free_token(current);
		current = next;
	}
	*token_lst = NULL;
}
