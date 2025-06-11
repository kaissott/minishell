#include "../../includes/minishell.h"

void	print_expand_lst(t_expand *lst, char *msg)
{
	size_t	i;

	i = 1;
	printf("\n%s\n", msg);
	if (!lst)
	{
		printf("The expand list is empty\n");
		return ;
	}
	while (lst)
	{
		printf("Node [%zu] :\n", i++);
		if (lst->value)
			printf("\tvalue : %s\n", lst->value);
		else
			printf("\tNo value\n");
		printf("\ttype : %d\n", lst->type);
		lst = lst->next;
	}
}

bool	lst_expand_add_back(t_expand **lst, t_expand *new)
{
	t_expand	*tmp;

	if (!lst || !new)
		return (false);
	if (!*lst)
	{
		*lst = new;
		return (true);
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (true);
}

t_expand	*create_expand(t_expand_type type, char *value)
{
	t_expand	*new_expand;

	if (!value)
		return (NULL);
	new_expand = ft_calloc(1, sizeof(t_expand));
	if (!new_expand)
	{
		free(value);
		return (NULL);
	}
	new_expand->type = type;
	new_expand->value = value;
	new_expand->next = NULL;
	return (new_expand);
}

char	*get_var_value(t_env **env_lst, char *var_name)
{
	pid_t	pid;
	t_env	*tmp;

	pid = getpid();
	tmp = *env_lst;
	if (ft_strcmp(var_name, "$$") == 0)
		return (ft_itoa(pid));
	else if (ft_strcmp(var_name, "$?") == 0)
		return (ft_itoa(errno));
	else if (ft_strcmp(var_name, "$") == 0)
		return (ft_strdup("$"));
	while (tmp)
	{
		if (ft_strcmp(tmp->var, var_name) == 0)
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (NULL);
}
