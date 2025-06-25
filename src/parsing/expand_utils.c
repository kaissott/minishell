#include "../../includes/minishell.h"

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
	size_t	name_len;

	*var_found = true;
	if (ft_strcmp(var_name, "$") == 0)
		return (ft_strdup("$"));
	if (ft_strcmp(var_name, "$$") == 0)
		return (ft_strdup("$$"));
	if (ft_strcmp(var_name, "$?") == 0)
		return (ft_itoa(shell->errcode));
	tmp = shell->env;
	name_len = ft_strlen(var_name);
	while (tmp)
	{
		if (ft_strncmp(tmp->env, var_name, name_len) == 0
			&& tmp->env[name_len] == '=')
			return (ft_strdup(tmp->env + name_len + 1));
		tmp = tmp->next;
	}
	*var_found = false;
	return (ft_strdup(""));
}

t_parse_error	replace_chunk_value(t_main *shell, t_expand **expand_lst,
		t_token *token, t_token_chunk *chunk)
{
	t_expand	*tmp;
	char		*var_value;
	t_expand	*next;
	bool		var_found;

	free(chunk->value);
	chunk->value = NULL;
	tmp = *expand_lst;
	var_found = false;
	next = NULL;
	while (tmp != NULL)
	{
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
		// printf("var found : %s\n", var_found ? "true" : "false");
		if (!var_found)
		{
			// printf("tmp->value before delone tmp : %s\n", tmp->value);
			expand_lst_delone(expand_lst, tmp);
			// print_expand_lst(*expand_lst,
			// 	"EXPAND LIST AFTER DELONE BLANK : \n");
			if (!chunk->value)
				chunk_lst_delone(&token->chunks, chunk);
			if (!token->chunks)
			{
				// print_token_lst(shell->token,
				// 	"TOKEN LIST BEFORE CHUNK DELONE : \n");
				token_lst_delone(&shell->token, token);
				// print_token_lst(shell->token,
				// 	"TOKEN LIST AFTER CHUNK DELONE : \n");
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
		if (tmp)
			tmp = next;
		else
			tmp = next->next;
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
