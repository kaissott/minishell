/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 02:29:02 by ludebion          #+#    #+#             */
/*   Updated: 2025/07/23 00:26:04 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

t_expand	*extract_expand_var(char *var, ssize_t *i)
{
	if (var[*i] == '$' || var[*i] == '?' || var[*i] == '/')
		return (create_expand(T_EXPAND_VAR, ft_substr(var, 0, 2)));
	while (var[*i] && (ft_isalnum(var[*i]) || var[*i] == '_'))
		(*i)++;
	return (create_expand(T_EXPAND_VAR, ft_substr(var, 1, *i - 1)));
}

static char	*get_var_value(t_main *shell, char *var_name, bool *var_found)
{
	t_env	*tmp;
	size_t	var_name_len;

	*var_found = true;
	if (ft_strcmp(var_name, "$") == 0)
		return (ft_strdup("$"));
	if (ft_strcmp(var_name, "$/") == 0)
		return (ft_strdup("$/"));
	if (ft_strcmp(var_name, "$$") == 0)
		return (ft_strdup("$$"));
	if (ft_strcmp(var_name, "$?") == 0)
		return (ft_itoa(shell->errcode));
	tmp = shell->env;
	var_name_len = ft_strlen(var_name);
	while (tmp)
	{
		if (ft_strncmp(tmp->env, var_name, var_name_len) == 0
			&& tmp->env[var_name_len] == '=')
			return (ft_strdup(tmp->env + var_name_len + 1));
		tmp = tmp->next;
	}
	*var_found = false;
	return ("");
}

static t_parse_error	handle_var_expansion(t_main *shell,
		t_expand **expand_lst, t_expand *tmp, t_token_chunk *chunk)
{
	char	*var_value;
	bool	var_found;

	var_found = false;
	if (tmp->type == T_EXPAND_VAR)
		var_value = get_var_value(shell, tmp->value, &var_found);
	else
	{
		var_found = true;
		var_value = tmp->value;
	}
	if (tmp->type == T_EXPAND_VAR)
		if (!var_value)
			return (ERR_MALLOC);
	if (!var_found)
		expand_lst_delone(expand_lst, tmp);
	else
	{
		chunk->value = join_or_dup(chunk->value, var_value);
		if (tmp->type == T_EXPAND_VAR && var_value)
			free(var_value);
		if (!chunk->value)
			return (ERR_MALLOC);
	}
	return (ERR_NONE);
}

t_parse_error	replace_chunk_value(t_main *shell, t_expand **expand_lst,
		t_token *token, t_token_chunk *chunk)
{
	t_expand		*tmp;
	t_expand		*next;
	t_parse_error	errcode;

	if (!*expand_lst)
		return (ERR_NONE);
	chunk->is_expanded = true;
	free(chunk->value);
	chunk->value = NULL;
	tmp = *expand_lst;
	while (tmp)
	{
		next = tmp->next;
		errcode = handle_var_expansion(shell, expand_lst, tmp, chunk);
		if (errcode != ERR_NONE)
			return (errcode);
		if (!chunk->value && !*expand_lst)
			chunk_lst_delone(&token->chunks, chunk);
		if (!token->chunks)
			token_lst_delone(&shell->token, token);
		tmp = next;
	}
	return (ERR_NONE);
}
