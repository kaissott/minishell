#include "../../includes/minishell.h"

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

bool	contains_ifs_chars(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
			return (true);
		i++;
	}
	return (false);
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

t_parse_error	replace_chunk_value(t_main *shell, t_expand **expand_lst,
		t_token *token, t_token_chunk *chunk)
{
	t_expand	*tmp;
	t_expand	*next;
	char		*var_value;
	bool		var_found;

	if (*expand_lst)
	{
		tmp = *expand_lst;
		chunk->is_expanded = true;
		free(chunk->value);
		chunk->value = NULL;
		while (tmp)
		{
			var_found = false;
			next = tmp->next;
			if (tmp->type == T_EXPAND_VAR)
			{
				var_value = get_var_value(shell, tmp->value, &var_found);
				if (!var_value)
					return (ERR_MALLOC);
			}
			else
			{
				var_found = true;
				var_value = tmp->value;
			}
			if (!var_found)
			{
				expand_lst_delone(expand_lst, tmp);
				if (!chunk->value && !*expand_lst)
					chunk_lst_delone(&token->chunks, chunk);
				if (!token->chunks)
				{
					token_lst_delone(&shell->token, token);
					return (ERR_NONE);
				}
			}
			else
			{
				chunk->value = join_or_dup(chunk->value, var_value);
				if (tmp->type == T_EXPAND_VAR && var_value)
					free(var_value);
				if (!chunk->value)
					return (ERR_MALLOC);
			}
			tmp = next;
		}
	}
	return (ERR_NONE);
}

void	free_expand_lst(t_expand **expand_lst)
{
	t_expand	*current;
	t_expand	*next;

	if (!expand_lst || !*expand_lst)
		return ;
	current = *expand_lst;
	while (current)
	{
		next = current->next;
		if (current->value)
			free(current->value);
		free(current);
		current = next;
	}
	*expand_lst = NULL;
}
