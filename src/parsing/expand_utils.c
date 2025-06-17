#include "../../includes/minishell.h"

static char	*get_var_value(t_main *shell, char *var_name)
{
	t_env	*tmp;
	pid_t	pid;
	size_t	name_len;

	if (!var_name)
		return (NULL);
	if (ft_strcmp(var_name, "$") == 0)
		return (ft_strdup("$"));
	if (ft_strcmp(var_name, "$$") == 0)
	{
		pid = getpid();
		return (ft_itoa(pid));
	}
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
}

t_parse_error	replace_chunk_value(t_main *shell, t_expand **expand_lst,
		t_token_chunk *chunk)
{
	t_expand	*tmp;
	char		*var_value;

	tmp = *expand_lst;
	chunk->value = NULL;
	while (tmp)
	{
		if (tmp->type == T_EXPAND_VAR)
			var_value = get_var_value(shell, tmp->value);
		else
			var_value = tmp->value;
		if (var_value)
			chunk->value = join_or_dup(chunk->value, var_value);
		if (tmp->type == T_EXPAND_VAR)
			free(var_value);
		if (!chunk->value)
			return (ERR_MALLOC);
		tmp = tmp->next;
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
		free(current->value);
		free(current);
		current = next;
	}
	*expand_lst = NULL;
}
